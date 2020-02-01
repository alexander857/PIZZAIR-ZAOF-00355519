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

//FUNCIONES PARA PEDIR LAS ORDENES

//funcion para ingresar una orden domicilio
void AddOrder(){
	//declaracion de variables
	int option = 0;
	
	//ingresan los datos del cliente
	ANORDER anorder;
	
	//igualando a cero los contadores, la variable de los montos y de los precios para que no agarren valores basura
	anorder.HOME.TotalamountDelivery = 0;
	anorder.HOME.delivery.price = 0;
	anorder.HOME.delivery.accountant.quantityStarter = 0;
	anorder.HOME.delivery.accountant.quantityStarter2 = 0;
	anorder.HOME.delivery.accountant.quantityStarter3 = 0;
	anorder.HOME.delivery.accountant.quantityMainDish = 0;
	anorder.HOME.delivery.accountant.quantityMainDish2 = 0;
	anorder.HOME.delivery.accountant.quantityMainDish3 = 0;
	anorder.HOME.delivery.accountant.quantityDrink = 0;
	anorder.HOME.delivery.accountant.quantityDrink2 = 0;
	anorder.HOME.delivery.accountant.quantityDrink3 = 0;

	cout << "\nNombre del cliente: "; getline(cin, anorder.HOME.delivery.name);
	cout << "Direccion: \n";
	cout << "\tNo.Casa: "; cin >> anorder.HOME.Address.HouseNumber; cin.ignore();
	cout << "\tColonia: "; getline(cin, anorder.HOME.Address.Suburb);
	cout << "\tMunicipio: "; getline(cin, anorder.HOME.Address.Municipality);
	cout << "\tDepartamento: "; getline(cin, anorder.HOME.Address.State);
	cout << "Telefono: "; getline(cin, anorder.HOME.phone);
	
	//INGRESANDO LA COMIDA Y BEBIDAS DE LA ORDEN A DOMICILIO
    bool follow = true;
    do{
        int option = 0;
	  	cout << "\nENTRADA:\n";
		cout << "\n1-Pan con ajo | 2-Pizza rolls | 3-Palitos de queso | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pStarter = garlicBread; 
            		anorder.HOME.delivery.price += 3.99; 
					anorder.HOME.delivery.accountant.quantityStarter += 1; break;
            case 2: anorder.HOME.delivery.pStarter2 = pizzaRolls; 
					anorder.HOME.delivery.price += 4.99; 
					anorder.HOME.delivery.accountant.quantityStarter2 += 1; break;
            case 3: anorder.HOME.delivery.pStarter3 = cheeseSticks; 
					anorder.HOME.delivery.price += 3.75; 
					anorder.HOME.delivery.accountant.quantityStarter3 += 1; break;
            case 4:follow = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
	follow = true;
    do{
        int option = 0;
	  	cout << "\nPLATO PRINCIPAL:\n";
		cout << "\n1-Pizza | 2-Pasta | 3-Lasagna | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pDish = pizza; 
            		anorder.HOME.delivery.price += 13.99; 
					anorder.HOME.delivery.accountant.quantityMainDish += 1; break;
            case 2: anorder.HOME.delivery.pDish2 = pasta; 				
					anorder.HOME.delivery.price += 5.55; 
					anorder.HOME.delivery.accountant.quantityMainDish2 += 1; break;
            case 3: anorder.HOME.delivery.pDish3 = lasagna; 
					anorder.HOME.delivery.price += 6.25; 
					anorder.HOME.delivery.accountant.quantityMainDish3 += 1; break;
            case 4:follow = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);

	follow = true;
    do{
        int option = 0;
	  	cout << "\nBEBIDA:\n";
		cout << "\n1-Cerveza | 2-Soda | 3-Te helado | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pDrink = beer; 
            		anorder.HOME.delivery.price += 1.99; 
					anorder.HOME.delivery.accountant.quantityDrink += 1; break;
            case 2: anorder.HOME.delivery.pDrink2 = soda; 				
					anorder.HOME.delivery.price += 0.95; 
					anorder.HOME.delivery.accountant.quantityDrink2 += 1; break;
            case 3: anorder.HOME.delivery.pDrink3 = tea; 	
					anorder.HOME.delivery.price += 1.15; 
					anorder.HOME.delivery.accountant.quantityDrink3 += 1; break;
            case 4:follow = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
	//guardando el monto total de la orden
	anorder.HOME.TotalamountDelivery = anorder.HOME.delivery.price;

    follow = true;
    do{
        int option = 0;
	  	cout << "\nTipo de pago:\n";
		cout << "\n1-Efectivo | 2-Tarjeta\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pay = cash; follow = false; break;
            case 2: anorder.HOME.delivery.pay = card; follow = false; break;			
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
    cout << "\nMonto total de la orden: $" << anorder.HOME.TotalamountDelivery << endl;

	//numero correlativo de la orden
	idDelivery++;
	anorder.HOME.idOrderDelivery = idDelivery;
	
	//agregando a al vector
	atDeliveryOrder.insert(atDeliveryOrder.end(), anorder);
	AnOrderDeliveryWasPlaced = true;
}

//funcion para ingresar una orden a restaurante
void AddOrder(int option){
	
	//ingresan los datos del cliente
	ANORDER anorder;

	//igualando a cero los contadores, la variable de los montos y de los precios para que no agarren valores basura
	anorder.RESTAURANT.TotalamountRestaurant = 0;
	anorder.RESTAURANT.Restaurant.price = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityStarter = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityStarter2 = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityStarter3 = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityMainDish = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityMainDish2 = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityMainDish3 = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityDrink = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityDrink2 = 0;
	anorder.RESTAURANT.Restaurant.accountant.quantityDrink3 = 0;
	
	cout << "\nNombre del cliente: "; getline(cin, anorder.RESTAURANT.Restaurant.name);
	cout << "Personas por mesa: "; cin >> anorder.RESTAURANT.PeoplePerTable; cin.ignore();

	//INGRESANDO LA COMIDA Y BEBIDAS DE LA ORDEN A RESTAURANTE
    bool follow = true;
    do{
        int option = 0;
	  	cout << "\nENTRADA:\n";
		cout << "\n1-Pan con ajo | 2-Pizza rolls | 3-Palitos de queso | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pStarter = garlicBread; 
            		anorder.RESTAURANT.Restaurant.price += 3.99; 
					anorder.RESTAURANT.Restaurant.accountant.quantityStarter += 1; break;
            case 2: anorder.RESTAURANT.Restaurant.pStarter2 = pizzaRolls; 
					anorder.RESTAURANT.Restaurant.price += 4.99; 
					anorder.RESTAURANT.Restaurant.accountant.quantityStarter2 += 1; break;
            case 3: anorder.RESTAURANT.Restaurant.pStarter3 = cheeseSticks; 
					anorder.RESTAURANT.Restaurant.price += 3.75; 
					anorder.RESTAURANT.Restaurant.accountant.quantityStarter3 += 1; break;
            case 4:follow = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
	follow = true;
    do{
        int option = 0;
	  	cout << "\nPLATO PRINCIPAL:\n";
		cout << "\n1-Pizza | 2-Pasta | 3-Lasagna | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pDish = pizza; 
            		anorder.RESTAURANT.Restaurant.price += 13.99; 
					anorder.RESTAURANT.Restaurant.accountant.quantityMainDish += 1; break;
            case 2: anorder.RESTAURANT.Restaurant.pDish2 = pasta; 				
					anorder.RESTAURANT.Restaurant.price += 5.55; 
					anorder.RESTAURANT.Restaurant.accountant.quantityMainDish2 += 1; break;
            case 3: anorder.RESTAURANT.Restaurant.pDish3 = lasagna; 
					anorder.RESTAURANT.Restaurant.price += 6.25; 
					anorder.RESTAURANT.Restaurant.accountant.quantityMainDish3 += 1; break;
            case 4:follow = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
	follow = true;
    do{
        int option = 0;
	  	cout << "\nBEBIDA:\n";
		cout << "\n1-Cerveza | 2-Soda | 3-Te helado | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pDrink = beer; 
            		anorder.RESTAURANT.Restaurant.price += 1.99; 
					anorder.RESTAURANT.Restaurant.accountant.quantityDrink += 1; break;
            case 2: anorder.RESTAURANT.Restaurant.pDrink2 = soda; 				
					anorder.RESTAURANT.Restaurant.price += 0.95; 
					anorder.RESTAURANT.Restaurant.accountant.quantityDrink2 += 1; break;
            case 3: anorder.RESTAURANT.Restaurant.pDrink3 = tea; 	
					anorder.RESTAURANT.Restaurant.price += 1.15; 
					anorder.RESTAURANT.Restaurant.accountant.quantityDrink3 += 1; break;
            case 4:follow = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
	anorder.RESTAURANT.TotalamountRestaurant = anorder.RESTAURANT.Restaurant.price;

    follow = true;
    do{
        int option = 0;
	  	cout << "\nTipo de pago:\n";
		cout << "\n1-Efectivo | 2-Tarjeta\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pay = cash; follow = false; break;
            case 2: anorder.RESTAURANT.Restaurant.pay = card; follow = false; break;			
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(follow);
	
	cout << "\nMonto total de la orden: $" << anorder.RESTAURANT.TotalamountRestaurant << endl; 
	
	//numero correlativo de la orden
	idRestaurant++;
	anorder.RESTAURANT.idOderRestaurant = idRestaurant;
	
	//agregando al vector
	atRestaurantOrder.insert(atRestaurantOrder.end(), anorder);
	AnOrderRestaurantWasPlaced = true;
	
}

//FUNCIONES PARA VER LAS ORDENES

//ver ordenes a domicilio
void SeeDeliveryOrder(int i){
	

	if(AnOrderDeliveryWasPlaced == false){
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(i == atDeliveryOrder.size()){
			
			cout << "\nSE HAN MOSTRADO TODAS LAS ORDENES A DOMICILIO!" << endl;

		}
		else{		
		
			cout << "\nORDEN " << atDeliveryOrder[i].HOME.idOrderDelivery << "\n" << endl;
			cout << "Nombre del cliente: " << atDeliveryOrder[i].HOME.delivery.name << endl;
			cout << "Direccion: ";
			cout << "No.Casa: " << atDeliveryOrder[i].HOME.Address.HouseNumber << ", ";
			cout << atDeliveryOrder[i].HOME.Address.Suburb << ", ";
			cout << atDeliveryOrder[i].HOME.Address.Municipality << ", ";
			cout << atDeliveryOrder[i].HOME.Address.State << endl;
			cout << "Telefono: " << atDeliveryOrder[i].HOME.phone << endl;

            //switch donde se muestran los platos y bebidas ordenados y cuantos de cada uno
 			cout << "\nEntrada: ";
            switch(atDeliveryOrder[i].HOME.delivery.pStarter){
                case garlicBread: cout << "Pan con ajo " << atDeliveryOrder[i].HOME.delivery.accountant.quantityStarter << " | ";
            }
            switch(atDeliveryOrder[i].HOME.delivery.pStarter2){
                case pizzaRolls: cout << "Pizza rolls " << atDeliveryOrder[i].HOME.delivery.accountant.quantityStarter2 << " | ";
            }
            switch(atDeliveryOrder[i].HOME.delivery.pStarter3){
                case cheeseSticks: cout << "Palitos de queso " << atDeliveryOrder[i].HOME.delivery.accountant.quantityStarter3 << endl; break;
            }
             
            cout << "\nPlato principal: ";
            switch(atDeliveryOrder[i].HOME.delivery.pDish){
                case pizza: cout << "Pizza " << atDeliveryOrder[i].HOME.delivery.accountant.quantityMainDish << " | ";
            }
            switch(atDeliveryOrder[i].HOME.delivery.pDish2){
                case pasta: cout << "Pasta " << atDeliveryOrder[i].HOME.delivery.accountant.quantityMainDish2 << " | ";
            }
            switch(atDeliveryOrder[i].HOME.delivery.pDish3){
                case lasagna: cout << "Lasagna " << atDeliveryOrder[i].HOME.delivery.accountant.quantityMainDish3 << endl; break;
            }
            
            cout << "\nBebida: ";
            switch( atDeliveryOrder[i].HOME.delivery.pDrink){
                case beer: cout << "Cerveza " << atDeliveryOrder[i].HOME.delivery.accountant.quantityDrink << " | "; 
            }
            switch( atDeliveryOrder[i].HOME.delivery.pDrink2){
                case soda: cout << "Soda " << atDeliveryOrder[i].HOME.delivery.accountant.quantityDrink2 << " | ";
            }
            switch( atDeliveryOrder[i].HOME.delivery.pDrink3){
                case tea: cout << "Te helado " << atDeliveryOrder[i].HOME.delivery.accountant.quantityDrink3; break;
            }
            
            cout << "\n\nTipo de pago: ";
             switch( atDeliveryOrder[i].HOME.delivery.pay){
                case cash: cout << "Efectivo" << endl; break;
                case card: cout << "Tarjeta" << endl; break;
            }
			cout << "Monto de la orden: $" << atDeliveryOrder[i].HOME.TotalamountDelivery << endl;
			
			i++;
		
			SeeDeliveryOrder(i);
			
		}	
		
	}

}

//ver ordenes a restaurante
void SeeRestaurantOrder(int n){
	

	if(AnOrderRestaurantWasPlaced == false){
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(n == atRestaurantOrder.size()){
			
			cout << "\nSE HAN MOSTRADO TODAS LAS ORDENES A RESTAURANTE!" << endl;

		}
		else{		
				
			cout << "\nORDEN " << atRestaurantOrder[n].RESTAURANT.idOderRestaurant << "\n" << endl;
			cout << "Nombre del cliente: " << atRestaurantOrder[n].RESTAURANT.Restaurant.name << endl;
			cout << "Personas por mesa: " << atRestaurantOrder[n].RESTAURANT.PeoplePerTable << endl;

            //switch donde se muestran todos los platos y bebidas de la orden y cuantos de cada uno
			cout << "\nEntrada: ";
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pStarter){
                case garlicBread: cout << "Pan con ajo " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityStarter << " | ";
            }
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pStarter2){
                case pizzaRolls: cout << "Pizza rolls " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityStarter2 << " | ";
            }
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pStarter3){
                case cheeseSticks: cout << "Palitos de queso " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityStarter3 << endl; break;
            }

            cout << "\nPlato principal: ";
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDish){
                case pizza: cout << "Pizza " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityMainDish << " | ";
            }
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDish2){
                case pasta: cout << "Pasta " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityMainDish2 << " | ";
            }
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDish3){
                case lasagna: cout << "Lasagna " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityMainDish3 << endl; break;
            }

            cout << "\nBebida: ";
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDrink){
                case beer: cout << "Cerveza " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityDrink << " | ";
            }
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDrink2){
                case soda: cout << "Soda " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityDrink2 << " | ";
            }
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDrink3){
                case tea: cout << "Te helado " << atRestaurantOrder[n].RESTAURANT.Restaurant.accountant.quantityDrink3; break;
            }

            cout << "\n\nTipo de pago: ";
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pay){
                case cash: cout << "Efectivo" << endl; break;
                case card: cout << "Tarjeta" << endl; break;
            }
			cout << "Monto de la orden: $" << atRestaurantOrder[n].RESTAURANT.TotalamountRestaurant << endl;
			
			n++;
			
			SeeRestaurantOrder(n);
			
		}	
		
	}

}

//FUNCIONES PARA DESPACHAR ORDENES

//despachar ordenes a domicilio
void DispatchDeliveryOrder(){
    //declaracion de variables
	int i = 0, k = 0;
    bool orderFound = false; 	
	string aName;
	
	if(AnOrderDeliveryWasPlaced == false){
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN PARA DESPACHAR!\033[0m" << endl;
		
	}
	else{
        cout << "\nNombre del cliente a despachar: "; getline(cin, aName);

        for(auto iter = atDeliveryOrder.begin(); iter != atDeliveryOrder.end(); ++iter){  
            if(iter->HOME.delivery.name == aName){
                if(k > 0){
                    cout << "\nHay alguien antes de " << aName << ", despache primero a " << atDeliveryOrder[i].HOME.delivery.name << endl;
                    orderFound = true;
                    break;
                }
                orderFound = true;
                amounts.push(atDeliveryOrder[i].HOME.TotalamountDelivery);	//guardando monto de la orden despachada en la pila de los montos
                DispatchHome.insert(DispatchHome.end(), atDeliveryOrder[i]);
                iter = atDeliveryOrder.erase(iter);
                cout << "\nLA ORDEN HA SIDO DESPACHADA CON EXITO!.\n";
            break;
            }
            else
                k++;

        }
        if(orderFound == false){
            cout << "\n\033[31mNo hay ninguna orden al nombre de: " << aName << "\033[0m" << endl;
        }

        //si ya no hay ordenes en el vector original, la bandera que indica que hay una orden se vuelve false
        if(atDeliveryOrder.size() == 0){
            AnOrderDeliveryWasPlaced = false;
        }
						
	}
	
}

//despachar ordenes a restaurante
void DispatchRestauranOrder(){
   //declaracion de variables
	int i = 0, k = 0;
    bool orderFound = false; 	
	string aName;
	
	if(AnOrderRestaurantWasPlaced == false){
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN PARA DESPACHAR!\033[0m" << endl;
		
	}
	else{
        cout << "\nNombre del cliente a despachar: "; getline(cin, aName);

        for(auto iter = atRestaurantOrder.begin(); iter != atRestaurantOrder.end(); ++iter){  

            if(iter->RESTAURANT.Restaurant.name == aName){  
                 if(k > 0){
                    cout << "\nHay alguien antes de " << aName << ", despache primero a " << atRestaurantOrder[i].RESTAURANT.Restaurant.name << endl;
                    orderFound = true;
                    break;
                }
                orderFound = true;      
                amounts.push(atRestaurantOrder[i].RESTAURANT.TotalamountRestaurant);	//guardando monto de la orden despachada en la pila de los montos
                DispatchRestaurant.insert(DispatchRestaurant.end(), atRestaurantOrder[i]);
                iter = atRestaurantOrder.erase(iter);
                cout << "\nLA ORDEN HA SIDO DESPACHADA CON EXITO!.\n";
            break;
            }
            else
                k++;
        }
        if(orderFound == false){
            cout << "\n\033[31mNo hay ninguna orden al nombre de: " << aName << "\033[0m" << endl;
		}
        //si ya no hay ordenes en el vector original, la bandera que indica que hay una orden se vuelve false
        if(atRestaurantOrder.size() == 0){
            AnOrderRestaurantWasPlaced = false;
        }
						
	}
	
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