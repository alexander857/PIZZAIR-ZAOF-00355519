#include<iostream>
#include<string.h>

using namespace std;

//registros

//direccion del cliente
struct CustomerAddress{

	int HouseNumber;
	string Suburb;
	string Municipality;
	string State;

};

//ordenes a domicilio
struct HomeOrders{
	
	string name;
	CustomerAddress Address;
	int phone;
	string MainDish;
	string StarterPlate;
	string drink;
	double amount;
	string PaymentType;
	
};

//pedidos a restaurante
struct CustomInRestaurant{
	
	string name;
	string PeoplePerTable;
	string MainDish;
	string StarterPlate;
	string drink;
	double amount;
	string PaymentType;
	
};

HomeOrders OrderList[5];
int NumberOfOrders = 0;

//PROTOTIPOS DE LAS FUNCIONES

void PizzaMenu(), OrderHomeDelivery(), OrderRestaurant();
int LogIn();

int main(){
	//DECLARACION DE VARIABLES 
	int N = 0;
	
	N = LogIn();		
					
	system("cls"); 
	PizzaMenu(); //se llama la funcion del menu principal
	
	return 0;
}

//menu principal del sistema de despacho
void PizzaMenu(){
	//variables de la funcion
	
	bool follow = true;
	
	do{
		int option = 0;
		//nombre de la pizzaria
		cout<<"PIZZAIR\n"<<endl;
		
		//menu de opciones
		cout<<"\n1-Agregar 1 pedido a domicilio\n";
		cout << "2-Agregar 1 encargo en restaurante\n";
		cout << "3-Ver pedidos a domicilio\n";
		cout << "4-Ver encargos en restaurante\n";
		cout << "5-Ver total de ventas\n";
		cout << "6-Cambiar de Usuario\n";
		cout << "7-Salir\n";
		cout << "\nOpcion: "; cin >> option;
		cin.ignore();

		switch(option){
			
			case 1: OrderHomeDelivery(); break;
			case 2: cout << "No disponible" << endl;
			case 3: cout << "No disponible" << endl;
			case 4: cout << "No disponible" << endl;
			case 5: cout << "No disponible" << endl;
			case 6: cout << "No disponible" << endl;
			case 7: follow = false;
			
		}		
		
	}while(follow);
}

//funcion donde se piden las ordenes a domicilio
void OrderHomeDelivery(){
	
    if(NumberOfOrders < 5){

       // Solicitar datos al usuario
        cout << "Nombre del Cliente: ";
        getline(cin, OrderList[NumberOfOrders].name);
        cout << "Direccion: \n";
        cout << "\tNo. Casa: ";
        cin >> OrderList[NumberOfOrders].Address.HouseNumber;
        cin.ignore();
        cout << "\tColonia: ";
        getline(cin, OrderList[NumberOfOrders].Address.Suburb);
        cout << "\tMunicipio: ";
        getline(cin, OrderList[NumberOfOrders].Address.Municipality);
        cout << "\tDepartamento: ";
        getline(cin, OrderList[NumberOfOrders].Address.State);
        cout << "Telefono: ";
        cin >> OrderList[NumberOfOrders].phone;
        cin.ignore();
        cout << "Plato principal: ";
        getline(cin, OrderList[NumberOfOrders].MainDish);
        cout << "Entrada: ";
        getline(cin, OrderList[NumberOfOrders].StarterPlate);
        cout << "Bebida: ";
        getline(cin, OrderList[NumberOfOrders].drink);
        cout << "Monto: $";
        cin >> OrderList[NumberOfOrders].amount;
		cin.ignore();
        cout << "Tipo de pago: ";
        getline(cin, OrderList[NumberOfOrders].PaymentType);
    //    cin.ignore();
        
        // Aumentar contador de cantidad de libros
        NumberOfOrders++;
    }
    else cout << "Error, maximo de pedidos!\n";
         
}

//funcion donde se piden las encargos a restaurante
void OrderRestaurant(){
	
	system("cls");
	
	if(NumberOfOrders < 5){
		
         // Solicitar datos al usuario
        cout << "Nombre del Cliente: ";
        getline(cin, RestaurantList[NumberOfOrders].name);
        cout << "Personas por mesa: ";
        getline(cin, RestaurantList[NumberOfOrders].PeoplePerTable);
        cout << "Plato principal: ";
        getline(cin, RestaurantList[NumberOfOrders].MainDish);      
        cout << "Entrada: ";
        getline(cin, RestaurantList[NumberOfOrders].StarterPlate);
        cout << "Bebida: ";
        getline(cin, RestaurantList[NumberOfOrders].drink);
 
        cout << "Monto: $";
        cin >> RestaurantList[NumberOfOrders].amount;
        cin.ignore();
        cout << "Tipo de pago: ";
        getline(cin, RestaurantList[NumberOfOrders].PaymentType);
		
		NumberOfOrders++;
	}
	
	else cout << "Error, maximo de pedidos!\n";	
	
}

//funcion de inicio de sesion
int LogIn(){
	//declaracion de variables
	char password[]="delete", key[6];
	int option = 0, k = 0;
	
	while(k == 0){
		
		//menu para elegir como se ingresara al sistema
		cout << "SOLO PERSONAL AUTORIZADO!\n" << endl;
		cout << "\n1.Iniciar sesion como Administrador\n";
		cout << "2.Iniciar sesion como Empleado\n";
		cout << "\nOpcion: "; cin >> option;
		
		if(option == 1){
			
			while(k == 0){
				cout << "Ingrese la clave: "; cin >> key;
				
				if(strcmp(password,key) == 0){
					return 0;
				}
			}	
		}
		else if(option == 2){
			
			return 1;
			
		}
	}	
}