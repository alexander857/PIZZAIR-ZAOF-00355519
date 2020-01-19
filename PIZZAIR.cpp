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
	int CorrelativeNumber;
	
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
	int CorrelativeNumber;
	
};

HomeOrders OrderList[5];
CustomInRestaurant RestaurantList[5];
int NumberOfOrders = 0;

//PROTOTIPOS DE LAS FUNCIONES

void PizzaMenu(), OrderHomeDelivery(), OrderRestaurant(), LookForHomeDelivery(), SearchRestaurantOrders(), TotalSales();
int LogIn();


int main(){
	//DECLARACION DE VARIABLES 
	int N = 0, k = 0;
	
	N = LogIn();		
	
	PizzaMenu(); //se llama la funcion del menu principal
	
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
		cout << "6-Cambiar de usuario\n";
		cout << "7-Salir\n";
		cout << "\nOpcion: "; cin >> option;
		cin.ignore();
		
		switch(option){
			
			case 1: OrderHomeDelivery(); break;
			case 2: OrderRestaurant(); break;
			case 3: LookForHomeDelivery(); break;
			case 4: SearchRestaurantOrders(); break;
			case 5: TotalSales(); break;
			case 6: LogIn(); break;
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
        cout << "Numero de la Orden: ";
        cin >> OrderList[NumberOfOrders].CorrelativeNumber;
        system("cls");
        
        // Aumentar contador de cantidad de libros
       NumberOfOrders++;
   }
   else cout << "Error, maximo de pedidos!\n";
         
}

//funcion donde se piden las encargos a restaurante
void OrderRestaurant(){
	
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
		cout << "Numero de la Orden: ";
        cin >> RestaurantList[NumberOfOrders].CorrelativeNumber;
        
        // Aumentar contador de cantidad de libros
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
				
				if(strcmp(password,key) == 0) return 0;
					
			}	
		}
		else if(option == 2) return 1;		
		
	}	
}

//funcion para buscar ordenes a domicilio
void LookForHomeDelivery(){
	//declaracion de variables
	string client;
	
	cout << "Ingrese el nombre del cliente: ";
	getline(cin, client);
	
	//buscando la orden del cliente ingresado
	for(int i = 0; i < NumberOfOrders; i++){
		
		if(client.compare(OrderList[i].name) == 0){
			
			cout << "Orden dle cliente ingresado:\n";
			cout << "Nombre: " << OrderList[i].name << '\n';
			cout << "Direccion:\n";
			cout << "\tNo. Casa: " << OrderList[i].Address.HouseNumber << '\n';
			cout << "\tColonia: " << OrderList[i].Address.Suburb << '\n';
			cout << "\tMunicipio: " << OrderList[i].Address.Municipality << '\n';
			cout << "\tDepartamento: " << OrderList[i].Address.State << '\n';
			cout << "Telefono: " << OrderList[i].phone << '\n';
			cout << "Plato Principal: " << OrderList[i].MainDish << '\n';
			cout << "Entrada: " << OrderList[i].StarterPlate << '\n';
			cout << "Bebida: " << OrderList[i].drink << '\n';
			cout << "Monto: $" << OrderList[i].amount << '\n';
			cout << "Tipo de pago: " << OrderList[i].PaymentType << '\n';
			cout << "Numero de la Orden: " << OrderList[i].CorrelativeNumber << '\n';
			cout << "\n";
			return;
		}
		
	}
	cout << "Orden no encontrada :( Quiza el nombre no esta registrado!" << endl;
}

//funcion de buscar las ordenes a restaurante
void SearchRestaurantOrders(){
	//declaracion de variables
	string client;
	
	cout << "Ingrese el nombre del cliente: ";
	getline(cin, client);
	
	//buscando la orden del cliente ingresado
	for(int i = 0; i < NumberOfOrders; i++){
		
		if(client.compare(OrderList[i].name) == 0){
			
			cout << "\nOrden del cliente ingresado:\n";
			cout << "Nombre: " << RestaurantList[i].name << '\n';
			cout << "Personas por mesa: " << RestaurantList[i].PeoplePerTable << '\n';
			cout << "Plato Principal: " << RestaurantList[i].MainDish << '\n';
			cout << "Entrada: " << RestaurantList[i].StarterPlate << '\n';
			cout << "Bebida: " << RestaurantList[i].drink << '\n';
			cout << "Monto: $" << RestaurantList[i].amount << '\n';
			cout << "Tipo de pago: " << RestaurantList[i].PaymentType << '\n';
			cout << "Numero de la Orden: " << RestaurantList[i].CorrelativeNumber << '\n';
			cout << "\n";
			return;
		}
		
	}
	cout << "Orden no encontrada :( Quiza el nombre no esta registrado!" << endl;
	
	
}

//funcion que calcula el total de ventas
void TotalSales(){
	//declaracion de variables
	double Total = 0;
	
	for(int i = 0; i < NumberOfOrders; i++){
		
		Total += OrderList[i].amount;
		Total += RestaurantList[i].amount;
		
	}
	
	cout << "Ventas Totales: $" << Total << endl; 
	
}