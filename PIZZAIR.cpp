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

//PROTOTIPOS DE LAS FUNCIONES

void OrderHomeDelivery(HomeOrders* Order, int size), OrderRestaurant(CustomInRestaurant* Restaurant, int size2);
void SearchRestaurantOrders(CustomInRestaurant* Restaurant, int size2), LookForHomeDelivery(HomeOrders* Order, int size);
void TotalSales(HomeOrders* Order, int size, CustomInRestaurant* Restaurant, int size2);
void DeleteHomeOrders(HomeOrders* Order, int size), DeleteOrdersRestaurant(CustomInRestaurant* Restaurant, int size2);
bool PizzaMenu();
int LogIn();


int main(){
	//DECLARACION DE VARIABLES 
	int N = 0, k = 0;
	bool A;	
		
	
	while(k == 0){
		
		N = LogIn();
		
		system("cls"); 
		A = PizzaMenu(); //se llama la funcion del menu principal
		
		//si A es false significa que el usuario en la funcion Pizza eligio salir, por lo tanto saldra del bucle while y termina el programa
		if(A == false){
			break;
		}
		//Caso contrario, A sea true significa que el usuario le dio cambiar de usuario y se mostrara nuevamente la funcion LogIn en el bucle while
	}			
	
	return 0;
}

//menu principal del sistema de despacho
bool PizzaMenu(){
	//variables de la funcion
	bool follow = true, Login = false;
	
	int size = 0, size2 = 0, N = 0;
	
	HomeOrders *OrderList;
	CustomInRestaurant *RestaurantList;		
	
	//se pide el numero de ordenes que se ingresaran
	cout << "\nCantidad de ordenes a domicilio a recibir: "; cin >> size;
	cout << "\nCantidad de encargos a restaurante por recibir: "; cin >> size2;
	
	//reservando memoria
	OrderList = new HomeOrders[size];
	RestaurantList = new CustomInRestaurant[size2];
	
	do{
		int option = 0;
		//nosbre de la pizzaria
		cout<<"\nPIZZAIR"<<endl;
		
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
			
			case 1: OrderHomeDelivery(OrderList, size); break;
			case 2: OrderRestaurant(RestaurantList, size2); break;
			case 3: LookForHomeDelivery(OrderList, size); break;
			case 4: SearchRestaurantOrders(RestaurantList, size2); break;
			case 5: TotalSales(OrderList, size, RestaurantList, size2); break;
			case 6: DeleteHomeOrders(OrderList, size); break;
			case 7: DeleteOrdersRestaurant(RestaurantList, size2); break;
			case 8: Login = true;
			case 9: follow = false;
			
		}	
		
	}while(follow || !Login);
	
	return follow || Login; //retorna true o false
}

//funcion donde se piden las ordenes a domicilio
void OrderHomeDelivery(HomeOrders* Order, int size){
	
     for(int i = 0; i < size; i++){
        // Solicitar datos al usuario
        cout << "\nNombre del Cliente: ";
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
        cout << "\nNombre del Cliente: ";
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

//funcion de inicio de sesion
int LogIn(){
	//declaracion de variables
	string password = "delete";
	string key;
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
				
				
				
				if(key.compare(password) == 0) return 0;
					
			}	
		}		
		else if(option == 2) return 1;
		
	}	
	
}

//funcion para buscar ordenes a domicilio
void LookForHomeDelivery(HomeOrders* Order, int size){
	//declaracion de variables
	string client;
	
	cout << "Ingrese el nombre del cliente: ";
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
	
	cout << "Ingrese el nombre del cliente: ";
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
	cout << "Orden no encontrada :( Quiza el nombre no esta registrado!" << endl;
	
	
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
	
	cout << "Ventas Totales: $" << VTotal << endl; 
	
}

//funcion para borrar ordenes
void DeleteHomeOrders(HomeOrders* Order, int size){
	
	//declaracion de variables
	string client;
	
	cout << "Ingrese el nombre del cliente que realizo la orden a eliminar: ";
	getline(cin, client);
	
	//eliminando orden del cliente ingresado
	for(int i = 0; i < size; i++){
		
		if(client.compare(Order[i].name) == 0){
			
			Order[i].name = " ";

			return;
		}
		
	}
	cout << "Orden no encontrada :( Quiza el nombre no esta registrado!" << endl;
	
}

//funcion de eliminar encargos a restaurante
void DeleteOrdersRestaurant(CustomInRestaurant* Restaurant, int size2){
	//declaracion de variables
	string client;
	
	cout << "Ingrese el nombre del cliente que realizo la orden a eliminar: ";
	getline(cin, client);
	
	//eliminando orden del cliente ingresado
	for(int i = 0; i < size2; i++){
		
		if(client.compare(Restaurant[i].name) == 0){
			
			Restaurant[i].name = " ";

			return;
		}
		
	}
	cout << "Orden no encontrada :( Quiza el nombre no esta registrado!" << endl;
		
}