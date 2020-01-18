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
	int PeoplePerTable;
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
			PizzaMenu(); //se llama la funcion del menu principal si la contrase��a es correcta
		
		}
		
		else{     //si no son iguaes las palabras, le sigue pidiendo que ingrese la clave hasta que ingrese la correcta
			
			system("cls");
			cout<<"Ingrese la clave: ";cin>>key;
			
		}	
						
	}
	
	return 0;
}

//menu principal del sistema de despacho
void PizzaMenu(){
	//variables de la funcion
	
	bool follow = true;
	
	do{
		int option = 0;
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
        cout << "Telefono: ";
        cin >> OrderList[NumberOfOrders].phone;
        cin.ignore();
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
        cout << "Direccion: \n";
        cout << "\tNo. Casa: ";
        cin >> OrderList[NumberOfOrders].Address.HouseNumber;
        cout << "\tColonia: ";
        getline(cin, OrderList[NumberOfOrders].Address.Suburb);
        cin.ignore();
        cout << "\tMunicipio: ";
        getline(cin, OrderList[NumberOfOrders].Address.Municipality);
        cin.ignore();
        cout << "\tDepartamento: ";
        getline(cin, OrderList[NumberOfOrders].Address.State);
        cin.ignore();
        
        // Aumentar contador de cantidad de libros
        NumberOfOrders++;
    }
    else cout << "Error, maximo de pedidos!\n";
         
}