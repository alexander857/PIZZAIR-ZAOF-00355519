#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

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
	HouseNumber Address;
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
	int PeoplePerTable;
	string MainDish;
	string StarterPlate;
	string drink;
	double amount;
	string PaymentType;
	
};



//PROTOTIPOS DE LAS FUNCIONES

char PizzaMenu(), OrderHomeDelivery(), OrderRestaurant();

int main(){
	//DECLARACION DE VARIABLES 
	//contrase?a para el menu principal
	char password[]="delete", key[6];  
	int k = 0, option = 0;	
	
	//menu para elegir como se ingresara al sistema
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout << "\n1.Iniciar sesion como Administrador\n";
	cout << "2.Iniciar sesion como Empleado\n";
	cout << "\nOpcion: "; cin >> option;
	
	if(option == 1){
		
		cout<<"Ingrese la clave: ";cin>>key;
		
	}
	
	while(k==0){
		
		//se compara si la contrase?a es correcta o si se inicio sesion como empleado
		if(strcmp(password,key) == 0 || option == 2){ //compara las dos palabras: password y key 
			
			system("cls"); 
			option = PizzaMenu(); //se llama la funcion del menu principal si la contrase��a es correcta
			system("cls");
		
		}
		
		else{     //si no son iguaes las palabras, le sigue pidiendo que ingrese la clave hasta que ingrese la correcta
			
			system("cls");
			cout<<"Ingrese la clave: ";cin>>key;
			
		}	
						
	}
	
	return 0;
}

//menu principal del sistema de despacho
char PizzaMenu(){
	//variables de la funcion
	int option;
	bool follow = true;
	
	do{
		
		//nosbre de la pizzaria
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
		
	}while(follow);
}

//funcion donde se piden las ordenes a domicilio
void OrderHomeDelivery(){
	
    if(NumberOfOrders < 5){
        // Solicitar datos al usuario
        cout << "Nombre del Cliente: ";
        getline(cin, OrderList[NumberOfOrders].name);
        cout << "Direccion: \n";
        cin >> OrderList[NumberOfOrders].Address.HouseNumber;
        cout << "Colonia: ";
        cin >> OrderList[NumberOfOrders].Address.Suburb;
        cout << "Municipio: ";
        cin >> OrderList[NumberOfOrders].Address.Municipality;
        cout << "Departamento: ";
        cin >> OrderList[NumberOfOrders].Address.State;
        cout << "\nTelefono: ";
        cin >> OrderList[NumberOfOrders].phone;
        cout << "Plato principal: ";
        cin >> OrderList[NumberOfOrders].MainDish;
        cout << "Entrada: ";
        cin >> OrderList[NumberOfOrders].StarterPlate;
        cout << "Bebida: ";
        cin >> OrderList[NumberOfOrders].drink;
        cout << "Monto: $";
        cin >> OrderList[NumberOfOrders].amount;
        cout << "Tipo de pago: ";
        cin >> OrderList[NumberOfOrders].PaymentType;
        
        cin.ignore();
        
        // Aumentar contador de cantidad de libros
        NumberOfOrders++;
    }
    else cout << "Error, maximo de pedidos!\n";
         
}