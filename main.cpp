#include<iostream>
#include<string>

//despues de los include van los define
#define PASSWORD "delete";

//luego el using namespace
using namespace std;

//luego enumeraciones
enum mainDish{pizza, pasta, lasagna};
enum drink{soda, tea};
enum starter{garlicBread, pizzaRolls, cheeseSticks};
enum pymentType{cash, card};

//luego las estructuras
struct address{

    string settlement, municipaly, department;
    int houseNumber;

};

struct mainInfo{

    string name;
    mainDish pDish;
    drink pDrink;
    starter pStarter;
    paymentType pay;
    int idOrder;
    int total;

};

struct delivery{

    address deliveryAddress;
    int callphone;
    mainInfo deliveryInfo;

};

struct houseOrder{

    int pTable;
    mainInfo houseInfo;

};

//variables globales
bool isAdmin = false;
int idOrder = 1;

//prototipos de las funciones
bool loginUser();
void printMenu();

int main(){
    //declaracion de variables y arreglos a usar
    delivery* dArray = NULL;
    houseOrder* hArray = NULL;
    int option = 0;

    //verificacion para iniciar sesion
    if(!loginUser()){  //loginUser() == false
        return 0;
    }

    //logica principal para la ejecucion del programa (menu)
    do{

        printMenu(); cin >> option;
        cin.ignore();

        switch(option){
            //agregar ordenes a domicilio
            case 1:
                addOrder(array);
            break;
            //agregar ordenes a restaurante
            case 2:
                addOrder(hArray);
            break;
            case 3:
            break;
            case 4:
            break;
            case 0:
            //nada
            break;
            default:
            break;
        }

    }while(option != 0);

    return 0;
}

bool loginUser(){

    string enterPass = " ";
    char option;
    cout << "INICIO DE SESION" << endl;
    cout << "A-Administrador" << endl;
    cout << "E- Empleado" << endl;
    cout << "Su opcion: "; cin >> option;

    switch(option){
        case 'a':
        case 'A':
            cout << "Digite la contrasena: "; cin >> enterPass;

            if(enterPass.compare(PASSWORD) == 0){
                isAdmin = true;
                return true;
            }
            else{
                cout << "Contrasena incorrecta" << endl;
            }
        break;
        case 'e':
        case 'E':
        isAdmin = false;
            return true;
        break;
    }
    return false;
}

void printMenu(){

    cout << "SISTEMA DE DESPACHO PIZZERIA PIZZAIR" << endl;
    cout << "1-Agregar ordenes a domicilio" << endl;
    cout << "2-Agregar ordenes a restaurante" << endl;
    cout << "3-Ver ordenes a domicilio" << endl;
    cout << "4-Ver ordenes a restaurante" << endl;
    cout << "Su opcion: ";
    

}

void addOrder(delivery* array){
    int size = 0, int aux = 0;
    cout << "Cantidad de pedidos a ingresar: "; cin >> size;
    cin.ignore();

    array = new delivery[size];

    for(int i = 0; i < size; i++){
        cout << "Nombre:\t"; getline(cin, array[i].deliveryInfo.name);
        cout << "Direccion:" << endl;
        cout << "Colonia:\t"; getline(cin, array[i].deliveryAddress.settlement);
        cout << "Municipio:\t"; getline(cin, array[i].deliveryAddress.municipaly);
        cout << "Departamento:\t"; getline(cin, array[i].deliveryAddress.department);
        cout << "No. Casa:\t"; cin >> array[i].deliveryAddress.houseNumber;
        cin.ignore();
        cout << "Plato principal" << endl;
        cout << "1- Pizza" << endl;
        cout << "2-Pasta" << endl;
        cout << "3- Lasagna" << endl;
        cout << "su opcion:\t"; cin >> aux;
        cin.ignore();

      //  aux --;

     //   array[i].deliveryInfo.pDish = aux;

        if(aux == 1){
            array[i].deliveryInfo.pDish = pizza;
        }
        else if(aux == 2){
            array[i].deliveryInfo.pDish = pasta;
        }
        else{
            array[i].deliveryInfo.pDish = lasagna;
        }

        cout << "Bebida" << endl;
        cout << "1- Soda" << endl;
        cout << "2-Tea" << endl;
        cout << "su opcion:\t"; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].deliveryInfo.pDrink = Soda;
        }
        else{
            array[i].deliveryInfo.pDrink = Tea;
        }

        array[i].deliveryInfo.idOrder = ideOrder++;

        cout << "Tipo de pago" << endl;
        cout << "1- Efectivo" << endl;
        cout << "2-Tarjeta" << endl;
        cout << "su opcion:\t"; cin >> aux;
        cin.ignore();

        if(aux == 1)
            array[i].deliveryInfo.pay = cash;
        else
            array[i].deliveryInfo.pay = card;

        cout << "Monto: "; cin >> array[i].deliveryInfo.total;
        cin.ignore(); 
        cout << "Telefono: "; cin >> array[i].callphone;
        cin.ignore();
    }


}

void addOrder(houseOrder* array){
     int size = 0, int aux = 0;
    cout << "Cantidad de pedidos a ingresar: "; cin >> size;
    cin.ignore();

    array = new houseOrder[size];

    for(int i = 0; i < size; i++){
        cout << "Nombre:\t"; getline(cin, array[i].houseInfo.name);
     
        cout << "Plato principal" << endl;
        cout << "1- Pizza" << endl;
        cout << "2-Pasta" << endl;
        cout << "3- Lasagna" << endl;
        cout << "su opcion:\t"; cin >> aux;
        cin.ignore();

      //  aux --;

     //   array[i].deliveryInfo.pDish = aux;

        if(aux == 1){
            array[i].houseInfo.pDish = pizza;
        }
        else if(aux == 2){
            array[i].houseInfo.pDish = pasta;
        }
        else{
            array[i].houseInfo.pDish = lasagna;
        }

        cout << "Bebida" << endl;
        cout << "1- Soda" << endl;
        cout << "2-Tea" << endl;
        cout << "su opcion:\t"; cin >> aux;
        cin.ignore();

        if(aux == 1){
            array[i].houseInfo.pDrink = Soda;
        }
        else{
            array[i].houseInfo.pDrink = Tea;
        }

        array[i].houseInfo.idOrder = ideOrder++;

        cout << "Tipo de pago" << endl;
        cout << "1- Efectivo" << endl;
        cout << "2-Tarjeta" << endl;
        cout << "su opcion:\t"; cin >> aux;
        cin.ignore();

        if(aux == 1)
            array[i].houseInfo.pay = cash;
        else
            array[i].houseInfo.pay = card;

        cout << "Monto: "; cin >> array[i].houseInfo.total;
        cin.ignore(); 
    }
}

void searchByName(delivery* array, int size){
    bool userExists = false;
    string aux = " ";
    cout << "Nombre a buscar: "; getline(cin, aux);

    for(int i = 0; i< size; i++){
        if(aux.compare(array[i].deliveryInfo.name) == 0){

            userExists = true;
            //imprimir datos
        }
    }                      //lo de aqui es si es true, lo  que va despues de los : es cuando es falso
    (!userExists) ? cout << "No existe el usuario" : cout << " "; //no existe el usuario
}

void searchByName(houseOrder* array, int size){
    bool userExists = false;
    string aux = " ";
    cout << "Nombre a buscar: "; getline(cin, aux);

    for(int i = 0; i< size; i++){
        if(aux.compare(array[i].houseInfo.name) == 0){

            userExists = true;
            //imprimir datos
        }
    }              //lo de aqui es si es true,       lo  que va despues de los : es cuando es falso
    (!userExists) ? cout << "No existe el usuario" : cout << " "; //no existe el usuario
}