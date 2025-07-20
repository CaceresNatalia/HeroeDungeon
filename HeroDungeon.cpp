/******************************************************************************

Aplicar los conceptos de Programación Orientada a Objetos (POO)
desarrollando un juego sencillo de batalla por turnos entre un Héroe (controlado por el
jugador) y un Enemigo (controlado por la computadora)..

*******************************************************************************/
#include <iostream>
#include <string>
#include <random>
#include <limits>
//CLases
class Enemigo;
class Jefe;
class Heroe{
    private: // los atributos de la clase se modifican mediante métodos públicos
        int nivel;
        int vida;
        int fuerza;
        int defensa;
        int agilidad;
        std::string nombre;
        std::string arma;
        bool escudo;
        bool escudoEq;
        int pociones[2];// 0: Fuerza. 1:Agilidad
        //bool amuleto;//cheat para llegar al final sin perder para pruebas
        bool pocUsada;




    public: //el usuario puede modificar directo desde el main
        Heroe(std::string nombre){
            this->nombre=nombre;
            this->nivel=1;
            this->vida=50;
            this->fuerza=25;
            this->agilidad=10;
            this->defensa=10;
            this->arma="Ninguna";
            this->escudo=false;
            this->escudoEq=false;
            //this->amuleto=true;//Cheat
            this->pocUsada=false;

            this->pociones[0]=0;
            this->pociones[1]=0;

        }

        int getNivel() const {return nivel;}
        int getVida() const {return vida;}
        int getAgi() const {return agilidad;}
        int getDef() const {return defensa;}
        std::string getNombre() const {return nombre;}

        ~Heroe(){}

        void registrarHeroe() {
        do {
            std::cout << "Ingrese su nombre: ";
            std::getline(std::cin, nombre);
            if (nombre.empty()) {
                std::cout << "El nombre no puede estar vacio. Intente de nuevo."<<std::endl;
            }
        } while (nombre.empty());
    }

    void equiparArma(){
            int opArma;

            if(nivel==4){
                if(arma=="Espada"){
                    fuerza-=10; //Desequipo la espada y restauro stats
                    agilidad-=5;
                }else if(arma=="Hacha"){
                    fuerza-=20; //Desequipo el hacha y restauro stats
                    agilidad+=5;
                }

                arma="Espada Celestial";
                fuerza+=20;
                agilidad+=8;
                std::cout<<"Tomas la espada recien adquirida. Puedes sentir su poder inundando tu cuerpo."<<std::endl;
            }else if(nivel <3 && arma=="Ninguna"){
            do{
            std::cout << "Elija una de las opciones previas (1 o 2): "<<std::endl;
            std::cin >> opArma;
            if (opArma>2 || opArma<1) {
                std::cout << "Opcion invalida. Intente de nuevo."<<std::endl;
            }
            } while (opArma<1 || opArma>2);

            if(opArma==1){//espada
                arma="Espada";
                fuerza+=10;
                agilidad+=5;
                std::cout<<"Te has equipado ESPADA!"<<std::endl;
            }else if (opArma==2){//Hacha
                arma="Hacha";
                fuerza+=20;
                agilidad-=5;
                std::cout<<"Te has equipado HACHA!"<<std::endl;

            }
            /*if(amuleto){
                agilidad+=80;
            }*/
    }
    }
    void equiparEscudo(){
            std::string esc;
            if(escudoEq){
                std::cout<<"Ya tienes equipado el escudo."<<std::endl;
            }else if(escudo){
            do {
                std::cout << "Seguro quieres equiparte ESCUDO? +10 Defensa -5 Agilidad (S/N): "<<std::endl;
                std::cin >> esc;
            if (esc!="S" && esc!="s") {
                std::cout << "Opcion invalida. Intente de nuevo."<<std::endl;
            }else{
                defensa+=10;
                agilidad-=5;
                escudoEq=true;
                std::cout<<"Te has equipado ESCUDO."<<std::endl;
            }
            } while (esc!="S" && esc !="s");
            }else if (!escudo){
                std::cout<<"No posees escudo que equipar."<<std::endl;
            }
    }


        void subirNivel(){
            nivel++;
            switch(nivel){
                case 2:
                    fuerza+=5;
                    agilidad+=5;
                    defensa+=5;
                    vida=75;
                std::cout<<nombre<<", nuestro aclamado heroe ha subido al nivel "<< nivel << "!"<<std::endl;
                std::cout<<"Al derrotar al engendro de las tinieblas, has obtenido: "<<std::endl;
                std::cout<<"ESCUDO -> +10 Defensa, -5 Agilidad."<<std::endl;
                escudo=true;
                break;
                case 3:
                    fuerza+=10;
                    agilidad+=5;
                    defensa+=5;
                    vida=100;
                std::cout<<nombre<<", nuestro aclamado heroe ha subido al nivel "<< nivel << "!"<<std::endl;
                std::cout<<"Al derrotar al engendro de las tinieblas, has obtenido: "<<std::endl;
                std::cout<<"POCION AGILIDAD -> +20 Agilidad durante 1 ronda cuando elijas beberla."<<std::endl;
                pociones[1]++;
                break;
                case 4:
                    fuerza+=15;
                    agilidad+=5;
                    defensa+=5;
                    vida=150;
                std::cout<<nombre<<", nuestro aclamado heroe ha subido al nivel "<< nivel << "!"<<std::endl;
                std::cout<<"Al derrotar al engendro de las tinieblas, has obtenido: "<<std::endl;
                std::cout<<"POCION FUERZA -> +20 Fuerza durante 1 turno cuando elijas beberla."<<std::endl;
                std::cout<<"ESPADA CELESTIAL -> +20 Fuerza + 8 Agilidad."<<std::endl;
                pociones[0]++;
                if(pocUsada){
                    agilidad-=20;
                }

                }

        }

        void atacar(Enemigo* enemigo);

        void recibirDanio(int d){
            vida -= (d-defensa);
            if(vida<0){
                vida=0;
            }
        std::cout<<"El ataque del enemigo fue exitoso! Tu vida queda en "<< vida <<std::endl;
        }

        void beberPocion(int pocion){
            if(pocion==1){ //Fuerza
                if(pociones[0]>0){
                std::cout<<"Has bebido una pocion de FUERZA. Sientes el poder inundando tu cuerpo. FUERZA +20."<<std::endl;
                fuerza+=20;
                pociones[0]--;
                }else{
                    std::cout<<"No quedan pociones de este tipo."<<std::endl;
                }
            }

            if(pocion==2){//Agilidad
                if(pociones[1]>0){
                std::cout<<"Has bebido una pocion de AGILIDAD. Sientes tu cuerpo mas liviano. AGILIDAD +20."<<std::endl;
                agilidad+=20;
                pociones[1]--;
                pocUsada=true;
                }else{
                    std::cout<<"No quedan pociones de este tipo."<<std::endl;
                }
            }


        }

        void mostrarStats(){
            std::cout<<"Tus stats actuales son los siguientes:"<<std::endl;
            std::cout<<"***************************************************" <<std::endl;
            std::cout<<"Nombre del Heroe: "<< nombre <<std::endl;
            std::cout<<"Nivel actual: "<< nivel <<std::endl;
            std::cout<<"Vida: "<< vida <<std::endl;
            std::cout<<"Fuerza: "<< fuerza <<std::endl;
            std::cout<<"Agilidad: "<< agilidad <<std::endl;
            std::cout<<"Defensa: "<< defensa <<std::endl;
            std::cout<<"Arma: "<< arma <<std::endl;
            if(escudoEq){
                std::cout<<"Escudo: Equipado."<<std::endl;
            }
            std::cout<<"***************************************************" <<std::endl;

        }

        void mostrarInventario(){
            std::cout<<"Posees los siguientes items en tu inventario:"<<std::endl;
            std::cout<<"***************************************************" <<std::endl;
            std::cout<<"Arma: "<< arma <<std::endl;
            if(nivel>=2){
                if(!escudoEq){
                  std::cout<<"Escudo: Desequipado."<<std::endl;
                }else{
                    std::cout<<"Escudo: Equipado."<<std::endl;
                }
            }

            for(int i= 0; i<=2; i++){
                if(pociones[i]>0){
                    switch(i){
                        case 0:
                        std::cout<<"Pocion de Fuerza: "<< pociones[0] << " u." <<std::endl;
                        break;
                        case 1:
                        std::cout<<"Pocion de Agilidad: "<< pociones[1] << " u." <<std::endl;
                        break;
                    }
                }
            }
            std::cout<<"***************************************************" <<std::endl;

        }
};
//---------------------------------------------------------------------------------------------------
class Enemigo{
    protected:
        int nivel;
        int vida;
        int fuerza;
        int defensa;
        int agilidad;
        std::string nombre;
        std::string arma;
        bool escudo;

        virtual void generarMonstruo(int nivelInicial) {
            switch(nivelInicial) {
                case 1:
                    this->vida = 50;
                    this->fuerza = 25;
                    this->agilidad = 10;
                    this->defensa = 10;
                    break;
                case 2:
                    this->vida = 75;
                    this->fuerza = 35;
                    this->agilidad = 15;
                    this->defensa = 15;
                    break;
                case 3:
                    this->vida = 100;
                    this->fuerza = 45;
                    this->agilidad = 20;
                    this->defensa = 20;
                    break;
                default:
                    this->vida = 50;
                    this->fuerza = 25;
                    this->agilidad = 10;
                    this->defensa = 10;
                    break;
            }
        }

    public:
        Enemigo(std::string nombre, int nivelInicial) {
            this->nombre = nombre;
            this->nivel = nivelInicial;
            generarMonstruo(nivelInicial);

        }

        int getNivel() const {return nivel;}
        int getVida() const {return vida;}
        int getAgi() const {return agilidad;}
        int getDef() const {return defensa;}
        std::string getNombre() const {return nombre;}


        void inicializar(int nivel){
                generarMonstruo(nivel);
            };

        virtual ~Enemigo() {}

        void equiparArma() {
            if(this->nivel == 1) {
                arma = "Garrote";
                fuerza += 5;
                agilidad -= 5;
                escudo = true;
                defensa += 10;
            } else if(this->nivel == 2) {
                arma = "Hacha";
                fuerza += 20;
                agilidad -= 5;
                escudo=false;
            } else if(this->nivel == 3) {
                arma = "Espada";
                fuerza += 10;
                agilidad += 5;
                escudo=false;
            } else if(this-> nivel == 4){
                arma = "Mazo";
                fuerza+=25;
                agilidad-=5;
                escudo=false;
            }
        }

        void mostrarStats(){
            std::cout<<"Los Stats del enemigo son los siguientes:"<<std::endl;
            std::cout<<"***************************************************" <<std::endl;
            std::cout<<"Nombre: "<< nombre <<std::endl;
            std::cout<<"Nivel: "<< nivel <<std::endl;
            std::cout<<"Vida: "<< vida <<std::endl;
            std::cout<<"Fuerza: "<< fuerza <<std::endl;
            std::cout<<"Agilidad: "<< agilidad <<std::endl;
            std::cout<<"Defensa: "<< defensa <<std::endl;
            std::cout<<"Arma: "<< arma <<std::endl;
            if(escudo){
                std::cout<<"Escudo: Equipado."<<std::endl;
            }

            std::cout<<"***************************************************" <<std::endl;

        }

        void atacar(Heroe* heroe){
            std::cout << "El enemigo te ataca con " << (fuerza-heroe->getDef()) << " de danio."<< std::endl;
            heroe->recibirDanio(fuerza);
        }

        void recibirDanio(int d){
            vida -= (d-defensa);
            if(vida<0){
                vida=0;
            std::cout<<"El ataque del heroe fue exitoso! La vida del monstruo queda en "<< vida <<std::endl;
            }else{
            std::cout<<"El ataque del heroe fue exitoso! La vida del monstruo queda en "<< vida <<std::endl;
            }

        }
};
//--------------------------------------------------------------------------------------------------
class Jefe : public Enemigo{
    protected:

    void generarMonstruo(int nivel) override{
        this->vida = 200;
        this->fuerza = 60;
        this->agilidad = 30;
        this->defensa = 30;
    }


    public:
    Jefe(std::string nombre, int nivelInicial): Enemigo(nombre, 4){ };

    void inicializar(int nivel){
        generarMonstruo(nivel);
    };


    void equiparArma(){
            arma = "Mazo";
            fuerza += 25;
            agilidad -= 5;
        }
};

        void Heroe::atacar(Enemigo* enemigo){
            std::cout << "Atacas al enemigo con " << (fuerza-enemigo->getDef()) << " de danio."<< std::endl;
            enemigo->recibirDanio(fuerza);
}

        int generarRandom(std::mt19937& gen){
        std::uniform_int_distribution<> dist(1,100);

        return dist(gen);
        }
    //--------------------------------------------------------------------------------------------------
class Batalla {
private:
    Heroe* heroe;
    Enemigo* enemigo;
    std::mt19937& gen;
    int turnosH;
    int turnosE;
    int golpesHeroe;
    int golpesEnemigo;
    float porcAHxturno;
    float porcAExturno;


public:
    Batalla(Heroe* heroe, Enemigo* enemigo, std::mt19937& g)
    : heroe(heroe),
      enemigo(enemigo),
      gen(g),
      turnosH(0),
      turnosE(0),
      golpesHeroe(0),
      golpesEnemigo(0),
      porcAHxturno(0),
      porcAExturno(0)
      {}

      ~Batalla() {
        heroe = nullptr;
        enemigo = nullptr;
}

    void iniciar() {
        int nroRandom;
        int probabilidad;

        while (heroe->getVida() > 0 && enemigo->getVida() > 0) {
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            // Turno del héroe
            turnosH++;
            std::cout << "Tu turno:" << std::endl;
            nroRandom = generarRandom(gen);
            probabilidad = nroRandom + heroe->getAgi() - enemigo->getAgi();

            if (probabilidad < 20) {
                std::cout << "Has errado el golpe!" << std::endl;
            } else {
                heroe->atacar(enemigo);
                golpesHeroe++;
            }


            if (enemigo->getVida() > 0) {
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            // Pausa para leer
            std::cout << "Presiona Enter para continuar...(quiza mas de una vez)"<<std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer
            std::cin.get(); // Espera a que el usuario presione Enter
            // Turno del enemigo (si sigue vivo)
                turnosE++;
                std::cout << "Turno enemigo:" << std::endl;
                nroRandom = generarRandom(gen);
                probabilidad = nroRandom + enemigo->getAgi() - heroe->getAgi();
                if (probabilidad < 20) {
                    std::cout << "El monstruo ha errado su golpe!" << std::endl;
                } else {
                    enemigo->atacar(heroe);
                    golpesEnemigo++;
                }
            }
            // Pausa para leer
            std::cout << "Presiona Enter para continuar...(quiza mas de una vez)"<<std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer
            std::cin.get(); // Espera a que el usuario presione Enter
        }

    }

    void mostrarEstadisticas()const{
        std::cout << "========= ESTADISTICAS DE BATALLA =========" << std::endl;
        std::cout << "Turnos heroe: " << turnosH << std::endl;
        std::cout << "Turnos enemigo: " << turnosE << std::endl;
        std::cout << "Golpes acertados por el heroe: " << golpesHeroe << std::endl;
        std::cout << "Golpes acertados por el enemigo: " << golpesEnemigo << std::endl;
        std::cout << "Porcentaje aciertos del heroe: " << (golpesHeroe*100)/turnosH <<"%."<< std::endl;
        std::cout << "Porcentaje aciertos del enemigo: " << (golpesEnemigo*100)/turnosE<<"%." << std::endl;
        std::cout << "===========================================" << std::endl;
        }


};
//Funciones generales
    void Menu(int opcion){
        std::cout << "============================================================" << std::endl;
        std::cout<<"Elige que curso de accion deseas tomar: "<<std::endl;
        std::cout<<"[1] Avanza para conocer a tu proximo enemigo."<<std::endl;
        std::cout<<"[2] Consultar tus stats."<<std::endl;
        std::cout<<"[3] Consultar tu inventario."<<std::endl;
        std::cout<<"[4] Consultar los stats del enemigo."<<std::endl;
        std::cout<<"[5] Beber Pocion."<<std::endl;
        std::cout<<"[6] Equipar escudo."<<std::endl;
        std::cout<<"[7] Iniciar la batalla."<<std::endl;
        std::cout<<"[0] Abandonar la mision, ya no estas para estos trotes."<<std::endl;
        std::cout << "============================================================" << std::endl;
        }



int main()
{
    //Inicializo random con semilla
    std::random_device rd;
    std::mt19937 gen(rd());
    Heroe* heroe1 = new Heroe("");
    Enemigo* monstruos[4]={nullptr};
    std::cout<<"Bienvenido, aclamado y necesario Heroe, a la Mazmorra Espectral!"<< std::endl;
    std::cout<<"Para embarcarte en la mision de aniquilar los monstruos que merodean este lugar, necesitamos que firmes aqui con tu nombre: " << std::endl;
    heroe1->registrarHeroe();
    std::cout<<"El gremio de guerreros te proporciona un arma para comenzar tu aventura."<<std::endl;
    std::cout<<"Elige sabiamente:"<<std::endl;
    std::cout<<"[1] ESPADA -> Fuerza +10, Agilidad +5."<<std::endl;
    std::cout<<"[2] HACHA -> Fuerza +20, Agilidad -5."<<std::endl;
    heroe1->equiparArma();
    std::cout<<"Todo esta listo para comenzar tu aventura!"<<std::endl;
    heroe1->mostrarStats();
    int opcion=-1;
    int pocion;
    Batalla* combate = nullptr;


    do{
    int nivHer;
    nivHer=heroe1->getNivel();
    //Creamos el monstruo según el nivel actual del héroe
    switch(nivHer){
        case 1:
            monstruos[0] = new Enemigo("Gollum", 1);
            monstruos[0]->inicializar(1);
            monstruos[0]->equiparArma();
        break;
        case 2:
           monstruos[1] = new Enemigo("Morgoth", 2);
           monstruos[1]->inicializar(2);
           monstruos[1]->equiparArma();
        break;
        case 3:
           monstruos[2] = new Enemigo("Pazuzu", 3);
           monstruos[2]->inicializar(2);
           monstruos[2]->equiparArma();
        break;
        default:
            monstruos[3] = new Jefe("Shoggoth", 4);
            monstruos[3]->inicializar(4);
            monstruos[3]->equiparArma();
        break;
    }

    Menu(opcion);
    std::cin >> opcion;

    switch(opcion){
        case 1:

            switch(nivHer){
                case 1:
                    std::cout<<"Ingresas a la tenebrosa mazmorra y al girar en el primer recodo cavernoso te chocas con tu primer enemigo."<<std::endl;
                    monstruos[0]->mostrarStats();
                break;
                case 2:
                    std::cout<<"Tras un razonable descanso, avanzas dentro de la oscura mazmorra. No pasa mucho tiempo hasta que oyes resoplidos cercanos."<<std::endl;
                    std::cout<<"Cuando tus ojos se acostumbran a la penumbra ves un orco mirandote con furia."<<std::endl;
                    monstruos[1]->mostrarStats();
                break;
                case 3:
                    std::cout<<"Te limpias la sangre del ultimo engendro pestilente, la adrenalina impulsa tu cuerpo a seguir avanzando."<<std::endl;
                    std::cout<<"Casi chocas con la mole que se yergue en el camino, enarbolas tu arma, listo para el combate."<<std::endl;
                    monstruos[2]->mostrarStats();
                break;
                default:
                    std::cout<<"Has llegado a lo mas profundo de la mazmorra, el aire esta viciado por el encierro y los horrores que pululaban por aqui. Ansias mas que nada poder derrotar al orco mas grande de todos."<<std::endl;
                    std::cout<<"El gigantesco ser no se hace esperar, cuando menos lo esperas, un mazazo te corta el paso y casi puedes sentir el aliento que escapa de entre sus colmillos descubiertos."<<std::endl;
                    std::cout<<"Sus ojos llenos de odio te miran expectantes, que vas a hacer al respecto?"<<std::endl;
                    monstruos[3]->mostrarStats();
                break;
            }

        break;

        case 2:
            heroe1->mostrarStats();
        break;

        case 3:
            heroe1->mostrarInventario();
        break;

        case 4:
            monstruos[nivHer-1]->mostrarStats();
        break;

        case 5:
            std::cout<<"Elige la pocion que deseas beber: "<<std::endl;
            std::cout<<"[1] FUERZA -> +20 de Fuerza durante una ronda."<<std::endl;
            std::cout<<"[2] AGILIDAD -> +20 de Agilidad durante una ronda."<<std::endl;
            std::cin >> pocion;
            if(pocion>0 && pocion<3){
            heroe1->beberPocion(pocion);
            }else{
            std::cout<<"La opcion ingresada no es valida."<<std::endl;

            }
        break;
        case 6:
            heroe1->equiparEscudo();
        break;
        case 7:{
            combate = new Batalla(heroe1, monstruos[nivHer - 1], gen);
            combate->iniciar();
            combate->mostrarEstadisticas();


            if(monstruos[nivHer-1]->getVida()==0){
                std::cout << "El monstruo " << monstruos[nivHer-1]->getNombre() << " ha sido abatido! Alabado sea nuestro heroe!" << std::endl;
                if(monstruos[nivHer-1]->getNombre()=="Shoggoth"){
                    std::cout << "La maxima amenaza del lugar ha sido liquidada, los aldeanos corren a organizar un festin en tu nombre. El rey sera informado de tus hazanias y recibiras una cuantiosa recompensa." << std::endl;
                    std::cout << "Tu reputacion como heroe crece a pasos agigantados, seras recordado en generaciones venideras por las canciones que relaten tu vida. No existe mayor recompensa para un heroe que esta forma de inmortalidad." << std::endl;
                    delete combate;
                    combate = nullptr;
                    return 0;
                }
                delete monstruos[nivHer-1];
                monstruos[nivHer-1]=nullptr;
                heroe1->subirNivel();
                nivHer=heroe1->getNivel();
                if(nivHer==4){
                    heroe1->equiparArma();
                }
            }



            if(heroe1->getVida()==0){
               std::cout<<"El heroe "<< heroe1->getNombre() << " ha sido derrotado! Que la gloria de sus victorias enaltezca su alma!" <<std::endl;
                delete heroe1;
                heroe1=nullptr;
                for(int i=0; i<4;i++){
                    delete monstruos[i];
                    monstruos[i]=nullptr;
                }
                delete combate;
                combate = nullptr;

                return 0;
            }

        }
        break;

        case 0:
            std::cout<<"Tomas los restos de tu equipamiento y arrastras tu cuerpo maltrecho fuera del Dungeon."<<std::endl;
            std::cout<<"La obtencion de la gloria no era tu destino inmediato, ya tendras tiempo de planificar futuras aventuras."<<std::endl;
        break;

        default:
            std::cout<<"Opcion invalida, intente de nuevo"<<std::endl;
        break;
    }


    }while(opcion!=0);
    delete heroe1;
    heroe1=nullptr;
    for(int i=0; i<4;i++){
    delete monstruos[i];
    monstruos[i]=nullptr;
    delete combate;
    combate = nullptr;
    }
    return 0;
}