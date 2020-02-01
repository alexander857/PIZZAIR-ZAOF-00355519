#include<iostream>
#include<string>
#include<queue>
#include<iomanip> //para la funcion redondear decimales
#include<stack>
#include <vector>
#include <algorithm>

//contraseña del sistema
#define PASSWORD "delete"
#define __Color_h__

using namespace std;

//ENUMERACIONES
//enumeraciones de los menus
enum starter{garlicBread, pizzaRolls, cheeseSticks};
enum mainDish{pizza, pasta, lasagna};
enum drink{beer, soda, tea};

//enumeracion de tipo de pago
enum paymentType{cash, card};

//REGISTROS

//direccion del cliente
struct CustomerAddress{
	
	string Suburb, Municipality, State;
	int HouseNumber;
	
};

//contadores de entradas, platos principales y bebidas ingresadas
struct counters{
	int quantityStarter, quantityStarter2, quantityStarter3;
	int quantityMainDish, quantityMainDish2, quantityMainDish3;
	int quantityDrink, quantityDrink2, quantityDrink3;
};

//info que tienen en comun los dos tipos de pedidos
struct mainData{
	
	string name;
	starter pStarter;
	starter pStarter2;
	starter pStarter3;
	mainDish pDish;
	mainDish pDish2;
	mainDish pDish3;
	drink pDrink;	
	drink pDrink2;
	drink pDrink3;
    paymentType pay;
	float price;
	counters accountant;
};

//pedidos a domicilio
struct DeliveryOrders{	

	CustomerAddress Address;
	string phone;
	mainData delivery;
	int idOrderDelivery;
	float TotalamountDelivery;
		
};

//pedidos a restaurante
struct RestaurantOrders{
	
	int PeoplePerTable;
	mainData Restaurant;
	int idOderRestaurant;
	float TotalamountRestaurant;
	
};

//una orden
struct AnOrder{
	
	DeliveryOrders HOME;
	RestaurantOrders RESTAURANT;
	
};

typedef struct AnOrder ANORDER;

//pedir todas las ordenes
struct AllOrders{
	queue <AnOrder> AtHome; //cola de pedidos a domicilio
	queue <AnOrder> AtRestaurant; //cola de pedidos a restaurante
	queue <AnOrder> printOrders; //cola auxiliar para guardar las ordenes cuando se van mostrando		
};

//vector de ordenes a domicilio
vector<AnOrder> atDeliveryOrder; 
//vector de ordenes a restaurante
vector<AnOrder> atRestaurantOrder;
//vector de ordenes a domicilio despachadas
vector<AnOrder> DispatchHome;
//vector de ordenes a restaurante despachadas
vector<AnOrder> DispatchRestaurant;

AllOrders allORDERS;

//VAIABLES GLOBALES
bool isAdmin = false, AnOrderDeliveryWasPlaced = false, AnOrderRestaurantWasPlaced = false;
int idDelivery = 0, idRestaurant = 0;

//pilas para almacenar el monto de las ordenes
stack<float> amounts; //montos sin IVA
stack<float> amountsIVA; //montos con IVA
stack<float> Extra;  //para guardar los montos originales y no eliminarlos

//PROTOTIPOS DE LAS FUNCIONES
bool LogIn(), PizzaMenu(); 
void AddOrder(), AddOrder(int option), SeeDeliveryOrder(int i), SeeRestaurantOrder(int n), DispatchDeliveryOrder(), DispatchRestauranOrder();
void WaitTimeDelibery(), WaitTimeRestaurant(), CancelOrder(), TotalSales();


int main(){
	
	 LogIn();
	 
	 PizzaMenu();
	
	return 0;
}

//menu principal del sistema de despacho
bool PizzaMenu(){
	//variables de la funcion
	bool follow = true;	
	
	do{
		int option = 0;
		//nombre de la pizzeria
		cout << "\nPIZZAIR" << endl;
		
		//menu de opciones
		cout << "\n1-Agregar orden a domicilio\n";
		cout << "2-Agregar orden en restaurante\n";
		cout << "3-Ver ordenes a domicilio\n";
		cout << "4-Ver ordenes en restaurante\n";
		cout << "5-Despachar ordenes a domicilio\n";
		cout << "6-Despachar ordenes en restaurante\n";
		cout << "7-Ver tiempo promedio de espera domicilio\n";
		cout << "8-Ver tiempo promedio de espera restaurante\n";
		cout << "9-Calcelar orden (domicilio o restaurante, solo Admin)\n";
		cout << "10-Calcular total de ventas\n";
		cout << "11-Cambiar de usuario\n";
		cout << "12-Salir\n";
		cout << "\nOpcion: "; cin >> option;
		cin.ignore();
		
		switch(option){
			//funciones llamadas al menu
			case 1: AddOrder(); break;
			case 2: AddOrder(0); break;
			case 3: SeeDeliveryOrder(0); break;
			case 4: SeeRestaurantOrder(0); break;
			case 5: DispatchDeliveryOrder(); break;
			case 6: DispatchRestauranOrder(); break;
			case 7: break;
			case 8: break;
			case 9: CancelOrder(); break;
			case 10: TotalSales(); break;
			case 11: LogIn(); break;
			case 12: follow = false; break;
			default: cout << "\nOPCION NO VALIDA!\n"; break;
			
		}	
		
	}while(follow);
	
}

//funcion de inicio de sesion
bool LogIn(){
	//declaracion de variables
	string key;
	char option = 0;
	int k = 0;
	
	do{
		
		//menu para elegir como se ingresara al sistema
		cout << "\nSOLO PERSONAL AUTORIZADO!\n" << endl;
		cout << "\n1.Iniciar sesion como Administrador\n";
		cout << "2.Iniciar sesion como Empleado\n";
		cout << "\nOpcion: "; cin >> option;
		
		switch(option){
			
			case '1':
				
				while(k == 0){
					//se pide la contraseña
					cout << "\nINGRESE LA CLAVE: "; cin >> key;				
					
					if(key.compare(PASSWORD) == 0){
						
						cout << "Ingresado como admin" << endl;
						isAdmin = true;
						k = 1;
					}			
				}
				break;	
				
			case '2':
				cout << "\nHa ingresado como Empleado" << endl;
				isAdmin = false;
				k = 1;
				break;
			default :
				cout << "\nOPCION NO VALIDA!" << endl;
				
		}

	}while(k == 0);		
}

//funcion donde se piden las ordenes a domicilio
void OrderHomeDelivery(HomeOrders* Order, int size){
	
     for(int i = 0; i < size; i++){
        // Solicitar datos al usuario
        cout << "\nNombre del Cliente "<< i + 1 <<": ";
        getline(cin, Order[i].name);
        cout << "Direccion: \n";
        cout << "\tNo. Casa: ";
        cin >> Order[i].Address.HouseNumber;
        cin.ignore();
        cout << "\tColonia: ";
        getline(cin, Order[i].Address.Suburb);
        cout << "\tMunicipio: ";
        getline(cin, Order[i].Address.Municipality);
        cout << "\tDepartamento: ";
        getline(cin, Order[i].Address.State);
        cout << "Telefono: ";
        cin >> Order[i].phone;
        cin.ignore();
        cout << "Plato principal: ";
        getline(cin, Order[i].MainDish);
        cout << "Entrada: ";
        getline(cin, Order[i].StarterPlate);
        cout << "Bebida: ";
        getline(cin, Order[i].drink);
        cout << "Monto: $";
        cin >> Order[i].amount;
        cin.ignore();
        cout << "Tipo de pago: ";
        getline(cin, Order[i].PaymentType);
        cout << "Numero de la Orden: ";
        cin >> Order[i].CorrelativeNumber;
        cin.ignore();
        cout << "\n";

   }
         
}

//funcion donde se piden las encargos a restaurante
void OrderRestaurant(CustomInRestaurant* Restaurant, int size2){
	
  for(int i = 0; i < size2; i++){
        // Solicitar datos al usuario
        cout << "\nNombre del Cliente "<< i + 1 <<": ";
        getline(cin, Restaurant[i].name);
        cout << "Personas por mesa: ";
        getline(cin, Restaurant[i].PeoplePerTable);
        cout << "Plato principal: ";
        getline(cin, Restaurant[i].MainDish);      
        cout << "Entrada: ";
        getline(cin, Restaurant[i].StarterPlate);
        cout << "Bebida: ";
        getline(cin, Restaurant[i].drink);
        cout << "Monto: $";
        cin >> Restaurant[i].amount;
        cin.ignore();
        cout << "Tipo de pago: ";
        getline(cin, Restaurant[i].PaymentType);
        cout << "Numero de la Orden: ";
        cin >> Restaurant[i].CorrelativeNumber;
        cin.ignore();
        cout << "\n";

   }
	
}

//funcion para buscar ordenes a domicilio
void LookForHomeDelivery(HomeOrders* Order, int size){
	//declaracion de variables
	string client;
	
	cout << "\nIngrese el nombre del cliente: ";
	getline(cin, client);
	
	//buscando la orden del cliente ingresado
	for(int i = 0; i < size; i++){
		
		if(client.compare(Order[i].name) == 0){
			
			cout << "\nOrden del cliente ingresado:\n";
			cout << "Nombre: " << Order[i].name << '\n';
			cout << "Direccion:\n";
			cout << "\tNo. Casa: " << Order[i].Address.HouseNumber << '\n';
			cout << "\tColonia: " << Order[i].Address.Suburb << '\n';
			cout << "\tMunicipio: " << Order[i].Address.Municipality << '\n';
			cout << "\tDepartamento: " << Order[i].Address.State << '\n';
			cout << "Telefono: " << Order[i].phone << '\n';
			cout << "Plato Principal: " << Order[i].MainDish << '\n';
			cout << "Entrada: " << Order[i].StarterPlate << '\n';
			cout << "Bebida: " << Order[i].drink << '\n';
			cout << "Monto: $" << Order[i].amount << '\n';
			cout << "Tipo de pago: " << Order[i].PaymentType << '\n';
			cout << "Numero de la Orden: " << Order[i].CorrelativeNumber << '\n';
			cout << "\n";
			return;
		}
	}
	cout << "\nOrden no encontrada :( Quiza el nombre no esta registrado!" << endl;
}

//funcion de buscar las ordenes a restaurante
void SearchRestaurantOrders(CustomInRestaurant* Restaurant, int size2){
	//declaracion de variables
	string client;
	
	cout << "\nIngrese el nombre del cliente: ";
	getline(cin, client);
	
	//buscando la orden del cliente ingresado
	for(int i = 0; i < size2; i++){
		
		if(client.compare(Restaurant[i].name) == 0){
			
			cout << "\nOrden del cliente ingresado:\n";
			cout << "Nombre: " << Restaurant[i].name << '\n';
			cout << "Personas por mesa: " << Restaurant[i].PeoplePerTable << '\n';
			cout << "Plato Principal: " << Restaurant[i].MainDish << '\n';
			cout << "Entrada: " << Restaurant[i].StarterPlate << '\n';
			cout << "Bebida: " << Restaurant[i].drink << '\n';
			cout << "Monto: $" << Restaurant[i].amount << '\n';
			cout << "Tipo de pago: " << Restaurant[i].PaymentType << '\n';
			cout << "Numero de la Orden: " << Restaurant[i].CorrelativeNumber << '\n';
			cout << "\n";
			return;
		}
		
	}
	cout << "\nOrden no encontrada :( Quiza el nombre no esta registrado!" << endl;
	
	
}

//funcion que calcula el total de ventas
void TotalSales(HomeOrders* Order, int size, CustomInRestaurant* Restaurant, int size2){
	//declaracion de variables
	double TotalH = 0, TotalR = 0, VTotal = 0;
	
	//sumando las ventas a domicilio
	for(int i = 0; i < size; i++){
		
		TotalH += Order[i].amount;
		
	}
	//sumando las ventas a restaurante
	for(int i = 0; i< size2; i++){
		
		TotalR += Restaurant[i].amount;
		
	}
	
	//sumando las ventas a domicilio y las ventas a restaurante y tenemos el total
	VTotal = TotalH + TotalR;
	
	cout << "\nVentas Totales: $" << VTotal << endl; 
	
}

//funcion para borrar ordenes a domicilio
void DeleteHomeOrders(HomeOrders* Order, int size, int &N){
	
	//declaracion de variables
	string client;
	
	if(N == 1){
		cout << "\nSOLO EL ADMINISTRADOR PUEDE HACER CAMBIOS EN LAS ORDENES!\n" << endl;
		return;
	}
	else{
		
		cout << "\nIngrese el nombre del cliente que realizo la orden a eliminar: ";
		getline(cin, client);
		
		//eliminando la orden del cliente ingresado
		for(int i = 0; i < size; i++){
			
			if(client.compare(Order[i].name) == 0){
				
				Order[i].name = "Esta orden ya no esta disponible, ha sido eliminada!";
				cout << "\nORDEN ELIMINADA!\n";
				return;
			}
			
		}
		cout << "\nOrden no encontrada :( Quiza el nombre no esta registrado!" << endl;	
		
	}
	
}

//funcion de eliminar encargos a restaurante
void DeleteOrdersRestaurant(CustomInRestaurant* Restaurant, int size2, int &N){
	//declaracion de variables
	string client;
	
	if(N == 1){
		cout << "\nSOLO EL ADMINISTRADOR PUEDE HACER CAMBIOS EN LAS ORDENES!\n" << endl;
		return;
	}
	else{
		
		cout << "\nIngrese el nombre del cliente que realizo la orden a eliminar: ";
		getline(cin, client);
		
		//eliminando la orden del cliente ingresado
		for(int i = 0; i < size2; i++){
			
			if(client.compare(Restaurant[i].name) == 0){
				
				Restaurant[i].name = "Esta orden ya no esta disponible, ha sido eliminada!";
				cout << "\nORDEN ELIMINADA!\n";
				return;
			}
			
		}
		cout << "\nOrden no encontrada :( Quiza el nombre no esta registrado!" << endl;
		
	}		
}

//funcion para ver pedidos a domicilio
void SeeHomeOrders(HomeOrders* Order, int size){
		
	//mostrando las ordenes a domicilio
	for(int i = 0; i < size; i++){
		
		if(Order[i].CorrelativeNumber != 0){
			
			cout << "\nPEDIDO "<< i + 1 <<":\n";
			cout << "Nombre: " << Order[i].name << '\n';
			cout << "Direccion:\n";
			cout << "\tNo. Casa: " << Order[i].Address.HouseNumber << '\n';
			cout << "\tColonia: " << Order[i].Address.Suburb << '\n';
			cout << "\tMunicipio: " << Order[i].Address.Municipality << '\n';
			cout << "\tDepartamento: " << Order[i].Address.State << '\n';
			cout << "Telefono: " << Order[i].phone << '\n';
			cout << "Plato Principal: " << Order[i].MainDish << '\n';
			cout << "Entrada: " << Order[i].StarterPlate << '\n';
			cout << "Bebida: " << Order[i].drink << '\n';
			cout << "Monto: $" << Order[i].amount << '\n';
			cout << "Tipo de pago: " << Order[i].PaymentType << '\n';
			cout << "Numero de la Orden: " << Order[i].CorrelativeNumber << '\n';
			cout << "\n";
			
		}
		else{
			cout << "\nAun no se ha ingresado ningun pedido a domicilio!" << endl;
			return;
		}					
	}		
}

//funcion para ver encargos a restaurante
void SeeRestaurantOrders(CustomInRestaurant* Restaurant, int size2){
		
	//mostrando las ordenes a domicilio
	for(int i = 0; i < size2; i++){
		
		if(Restaurant[i].CorrelativeNumber != 0){
			
			cout << "\nPEDIDO "<< i + 1 <<":\n";
			cout << "Nombre: " << Restaurant[i].name << '\n';
			cout << "Personas por mesa: " << Restaurant[i].PeoplePerTable << '\n';
			cout << "Plato Principal: " << Restaurant[i].MainDish << '\n';
			cout << "Entrada: " << Restaurant[i].StarterPlate << '\n';
			cout << "Bebida: " << Restaurant[i].drink << '\n';
			cout << "Monto: $" << Restaurant[i].amount << '\n';
			cout << "Tipo de pago: " << Restaurant[i].PaymentType << '\n';
			cout << "Numero de la Orden: " << Restaurant[i].CorrelativeNumber << '\n';
			cout << "\n";
					
		}
		else{
			cout << "\nAun no se ha ingresado ningun encargo a restaurante!" << endl;
			return;
		}					
	}		
}