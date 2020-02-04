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

//info que tienen en comun los dos tipos de pedidos
struct mainData{
	
	string name;
	starter pStarter[3];
	mainDish pDish[3];
	drink pDrink[3];
	vector<starter> pS;
	vector<mainDish> pD;
	vector<drink> pDr;	
    paymentType pay;
	float price;
	int id;
};

//pedidos a domicilio
struct DeliveryOrders{	

	CustomerAddress Address;
	string phone;
	mainData delivery;
	int idOrderDelivery, quantitiesD[9]; //para guardar las cantidades de entradas, platos y bebidas
	float TotalamountDelivery;
		
};

//pedidos a restaurante
struct RestaurantOrders{
	
	int PeoplePerTable, idOderRestaurant, quantitiesR[9]; //para guardar las cantidades de entradas, platos y bebidas
	mainData Restaurant;
	float TotalamountRestaurant;
	
};

//una orden
struct AnOrder{
	
	DeliveryOrders HOME;
	RestaurantOrders RESTAURANT;
	
};

typedef struct AnOrder ANORDER;

//vector de ordenes a domicilio
vector<AnOrder> atDeliveryOrder; 
//vector de ordenes a restaurante
vector<AnOrder> atRestaurantOrder;
//vector de ordenes a domicilio despachadas
vector<AnOrder> DispatchHome;
//vector de ordenes a restaurante despachadas
vector<AnOrder> DispatchRestaurant;

//VAIABLES GLOBALES
bool isAdmin = false, AnOrderDeliveryWasPlaced = false, AnOrderRestaurantWasPlaced = false, requested = false;
int id = 0;

//pila para almacenar el monto de las ordenes
stack<float> amounts; //montos sin IVA

//PROTOTIPOS DE LAS FUNCIONES
bool LogIn(), PizzaMenu(); 
void AddOrder(), AddOrder(int option), SeeDeliveryOrder(int i), SeeRestaurantOrder(int n), DispatchDeliveryOrder(), DispatchRestauranOrder();
void WaitTimeDelibery(int i, float TotalTimeOuts), WaitTimeRestaurant(int i, float TotalTimeOuts), CancelOrder(), TotalSales();


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
		cout << "\n\033[36mPIZZAIR\033[0m" << endl;
		
		//menu de opciones
		
		cout << "\n1-Agregar orden a domicilio\n";
		cout << "2-Agregar orden en restaurante\n";
		cout << "3-Ver ordenes a domicilio\n";
		cout << "4-Ver ordenes en restaurante\n";
		cout << "5-Despachar ordenes a domicilio\n";
		cout << "6-Despachar ordenes en restaurante\n";
		cout << "7-Ver tiempo promedio de espera domicilio\n";
		cout << "8-Ver tiempo promedio de espera restaurante\n";
		cout << "9-Calcelar orden (domicilio o restaurante, \033[31msolo Admin\033[0m)\n";
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
			case 7: WaitTimeDelibery(0, 0); break;
			case 8: WaitTimeRestaurant(0, 0); break;
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
						
						cout << "\n\033[33mHAS INICIADO SESION COMO ADMIN!\033[0m" << endl;
						isAdmin = true;
						k = 1;
					}			
				}
				break;	
				
			case '2':
				cout << "\n\033[33mHAS INICIADO SESION COMO EMPLEADO!\033[0m" << endl;
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
	
	//igualando a cero el arreglo contador, la variable de los montos y de los precios para que no agarren valores basura
	anorder.HOME.TotalamountDelivery = 0;
	anorder.HOME.delivery.price = 0;

	for(int i = 0; i < 9; i++){
		anorder.HOME.quantitiesD[i] = 0;
	}

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
    
	  	cout << "\nENTRADA:\n";
		cout << "\n1-Pan con ajo | 2-Pizza rolls | 3-Palitos de queso | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pStarter[0] = garlicBread; 
            		anorder.HOME.delivery.price += 3.99; 
					anorder.HOME.quantitiesD[0] += 1;
					requested = true; break;
            case 2: anorder.HOME.delivery.pStarter[1] = pizzaRolls; 
					anorder.HOME.delivery.price += 4.99; 
					anorder.HOME.quantitiesD[1] += 1;
					requested = true; break;
            case 3: anorder.HOME.delivery.pStarter[2] = cheeseSticks; 
					anorder.HOME.delivery.price += 3.75; 
					anorder.HOME.quantitiesD[2] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
    }while(follow);
	
	follow = true;
    do{
    
	  	cout << "\nPLATO PRINCIPAL:\n";
		cout << "\n1-Pizza | 2-Pasta | 3-Lasagna | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pDish[0] = pizza; 
            		anorder.HOME.delivery.price += 13.99; 
					anorder.HOME.quantitiesD[3] += 1;
					requested = true; break;
            case 2: anorder.HOME.delivery.pDish[1] = pasta; 				
					anorder.HOME.delivery.price += 5.55; 
					anorder.HOME.quantitiesD[4] += 1;
					requested = true; break;
            case 3: anorder.HOME.delivery.pDish[2] = lasagna; 
					anorder.HOME.delivery.price += 6.25; 
					anorder.HOME.quantitiesD[5] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
    }while(follow);

	follow = true;
    do{

	  	cout << "\nBEBIDA:\n";
		cout << "\n1-Cerveza | 2-Soda | 3-Te helado | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pDrink[0] = beer; 
            		anorder.HOME.delivery.price += 1.99; 
					anorder.HOME.quantitiesD[6] += 1;
					requested = true; break;
            case 2: anorder.HOME.delivery.pDrink[1] = soda; 				
					anorder.HOME.delivery.price += 0.95; 
					anorder.HOME.quantitiesD[7] += 1;
					requested = true; break;
            case 3: anorder.HOME.delivery.pDrink[2] = tea; 	
					anorder.HOME.delivery.price += 1.15; 
					anorder.HOME.quantitiesD[8] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
    }while(follow);
	
	//guardando el monto total de la orden
	anorder.HOME.TotalamountDelivery = anorder.HOME.delivery.price;

    follow = true;
	if(requested == true){

		do{

			cout << "\nTipo de pago:\n";
			cout << "\n1-Efectivo | 2-Tarjeta\n";
			cout << "Opcion: "; cin >> option;
			switch(option){
				case 1: anorder.HOME.delivery.pay = cash; follow = false; break;
				case 2: anorder.HOME.delivery.pay = card; follow = false; break;			
				default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
			}
		}while(follow);
		
		cout << "\nMonto total de la orden: $" << anorder.HOME.TotalamountDelivery << endl;

		//numero correlativo de la orden
		id++;
		anorder.HOME.delivery.id = id;
		
		//agregando a al vector
		atDeliveryOrder.insert(atDeliveryOrder.end(), anorder);
		AnOrderDeliveryWasPlaced = true;
		requested = false; //verifica si se pidio algo en la orden
	}
	else cout << "\nEsta orden no sera guardada ya que no se pidio ninguna cosa!" << endl;
}

//funcion para ingresar una orden a restaurante
void AddOrder(int option){
	
	//ingresan los datos del cliente
	ANORDER anorder;

	//igualando a cero el arreglo contador, la variable de los montos y de los precios para que no agarren valores basura
	anorder.RESTAURANT.TotalamountRestaurant = 0;
	anorder.RESTAURANT.Restaurant.price = 0;

	for(int i = 0; i < 9; i++){
		anorder.RESTAURANT.quantitiesR[i] = 0;
	}
	
	cout << "\nNombre del cliente: "; getline(cin, anorder.RESTAURANT.Restaurant.name);
	cout << "Personas por mesa: "; cin >> anorder.RESTAURANT.PeoplePerTable; cin.ignore();

	//INGRESANDO LA COMIDA Y BEBIDAS DE LA ORDEN A RESTAURANTE
    bool follow = true;
    do{
    
	  	cout << "\nENTRADA:\n";
		cout << "\n1-Pan con ajo | 2-Pizza rolls | 3-Palitos de queso | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pStarter[0] = garlicBread; 
            		anorder.RESTAURANT.Restaurant.price += 3.99; 
					anorder.RESTAURANT.quantitiesR[0] += 1; 
					requested = true; break;
            case 2: anorder.RESTAURANT.Restaurant.pStarter[1] = pizzaRolls; 
					anorder.RESTAURANT.Restaurant.price += 4.99; 
					anorder.RESTAURANT.quantitiesR[1] += 1; 
					requested = true; break;
            case 3: anorder.RESTAURANT.Restaurant.pStarter[2] = cheeseSticks; 
					anorder.RESTAURANT.Restaurant.price += 3.75; 
					anorder.RESTAURANT.quantitiesR[2] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
    }while(follow);
	
	follow = true;
    do{
    
	  	cout << "\nPLATO PRINCIPAL:\n";
		cout << "\n1-Pizza | 2-Pasta | 3-Lasagna | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pDish[0] = pizza; 
            		anorder.RESTAURANT.Restaurant.price += 13.99; 
					anorder.RESTAURANT.quantitiesR[3] += 1;
					requested = true; break;
            case 2: anorder.RESTAURANT.Restaurant.pDish[1] = pasta; 				
					anorder.RESTAURANT.Restaurant.price += 5.55; 
					anorder.RESTAURANT.quantitiesR[4] += 1;
					requested = true; break;
            case 3: anorder.RESTAURANT.Restaurant.pDish[2] = lasagna; 
					anorder.RESTAURANT.Restaurant.price += 6.25; 
					anorder.RESTAURANT.quantitiesR[5] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
    }while(follow);
	
	follow = true;
    do{
    
	  	cout << "\nBEBIDA:\n";
		cout << "\n1-Cerveza | 2-Soda | 3-Te helado | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pDrink[0] = beer; 
            		anorder.RESTAURANT.Restaurant.price += 1.99; 
					anorder.RESTAURANT.quantitiesR[6] += 1;
					requested = true; break;
            case 2: anorder.RESTAURANT.Restaurant.pDrink[1] = soda; 				
					anorder.RESTAURANT.Restaurant.price += 0.95; 
					anorder.RESTAURANT.quantitiesR[7] += 1;
					requested = true; break;
            case 3: anorder.RESTAURANT.Restaurant.pDrink[2] = tea; 	
					anorder.RESTAURANT.Restaurant.price += 1.15; 
					anorder.RESTAURANT.quantitiesR[8] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
    }while(follow);
	
	anorder.RESTAURANT.TotalamountRestaurant = anorder.RESTAURANT.Restaurant.price;

    follow = true;
	if(requested == true){

		do{

			cout << "\nTipo de pago:\n";
			cout << "\n1-Efectivo | 2-Tarjeta\n";
			cout << "Opcion: "; cin >> option;
			switch(option){
				case 1: anorder.RESTAURANT.Restaurant.pay = cash; follow = false; break;
				case 2: anorder.RESTAURANT.Restaurant.pay = card; follow = false; break;			
				default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
			}
		}while(follow);

		cout << "\nMonto total de la orden: $" << anorder.RESTAURANT.TotalamountRestaurant << endl;

		//numero correlativo de la orden
		id++;
		anorder.RESTAURANT.Restaurant.id = id;
		
		//agregando al vector
		atRestaurantOrder.insert(atRestaurantOrder.end(), anorder);
		AnOrderRestaurantWasPlaced = true;
		requested = false; //verifica si se pidio algo en la orden
	}
	else cout << "\nEsta orden no sera guardada ya que no se pidio ninguna cosa!" << endl;
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
		
			cout << "\n\033[34mORDEN " << atDeliveryOrder[i].HOME.delivery.id << "\033[0m\n" << endl;
			cout << "Nombre del cliente: " << atDeliveryOrder[i].HOME.delivery.name << endl;
			cout << "Direccion: ";
			cout << "No.Casa: " << atDeliveryOrder[i].HOME.Address.HouseNumber << ", ";
			cout << atDeliveryOrder[i].HOME.Address.Suburb << ", ";
			cout << atDeliveryOrder[i].HOME.Address.Municipality << ", ";
			cout << atDeliveryOrder[i].HOME.Address.State << endl;
			cout << "Telefono: " << atDeliveryOrder[i].HOME.phone << endl;

            //switch donde se muestran los platos y bebidas ordenados y cuantos de cada uno
 			cout << "\nEntrada: ";
             for(int j = 0; j < 3; j++){

                switch(atDeliveryOrder[i].HOME.delivery.pStarter[j]){
                    case garlicBread: cout << "Pan con ajo " << atDeliveryOrder[i].HOME.quantitiesD[0] << " | "; break;
                    case pizzaRolls: cout << "Pizza rolls " << atDeliveryOrder[i].HOME.quantitiesD[1] << " | "; break;
                    case cheeseSticks: cout << "Palitos de queso " << atDeliveryOrder[i].HOME.quantitiesD[2] << " | "; break;
                }

             }
             
            cout << "\nPlato principal: ";
            for(int j = 0; j< 3; j++){

                switch(atDeliveryOrder[i].HOME.delivery.pDish[j]){ 
                    case pizza: cout << "Pizza " << atDeliveryOrder[i].HOME.quantitiesD[3] << " | "; break;
                    case pasta: cout << "Pasta " << atDeliveryOrder[i].HOME.quantitiesD[4] << " | "; break;
                    case lasagna: cout << "Lasagna " << atDeliveryOrder[i].HOME.quantitiesD[5] << " | "; break;
                }

            }
            
            cout << "\nBebida: ";
            for(int j = 0; j < 3; j++){

                switch( atDeliveryOrder[i].HOME.delivery.pDrink[j]){
                    case beer: cout << "Cerveza " << atDeliveryOrder[i].HOME.quantitiesD[6] << " | "; break;
                    case soda: cout << "Soda " << atDeliveryOrder[i].HOME.quantitiesD[7] << " | "; break;
                    case tea: cout << "Te helado " << atDeliveryOrder[i].HOME.quantitiesD[8] << " | "; break; 
                }

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
				
			cout << "\n\033[34mORDEN " << atRestaurantOrder[n].RESTAURANT.Restaurant.id << "\033[m\n" << endl;
			cout << "Nombre del cliente: " << atRestaurantOrder[n].RESTAURANT.Restaurant.name << endl;
			cout << "Personas por mesa: " << atRestaurantOrder[n].RESTAURANT.PeoplePerTable << endl;

            //switch donde se muestran todos los platos y bebidas de la orden y cuantos de cada uno
			cout << "\nEntrada: ";
            for(int i = 0; i < 3; i++){

                switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pStarter[i]){
                    case garlicBread: cout << "Pan con ajo " << atRestaurantOrder[n].RESTAURANT.quantitiesR[0] << " | "; break;
                    case pizzaRolls: cout << "Pizza rolls " << atRestaurantOrder[n].RESTAURANT.quantitiesR[1] << " | "; break;
                    case cheeseSticks: cout << "Palitos de queso " << atRestaurantOrder[n].RESTAURANT.quantitiesR[2] << " | "; break;
                }

            }

            cout << "\nPlato principal: ";
            for(int i = 0; i < 3; i++){

                switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDish[i]){
                    case pizza: cout << "Pizza " << atRestaurantOrder[n].RESTAURANT.quantitiesR[3] << " | "; break;
                    case pasta: cout << "Pasta " << atRestaurantOrder[n].RESTAURANT.quantitiesR[4] << " | "; break;
                    case lasagna: cout << "Lasagna " << atRestaurantOrder[n].RESTAURANT.quantitiesR[5] << " | "; break;
                }

            }

            cout << "\nBebida: ";
            for(int i = 0; i < 3; i++){

                switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDrink[i]){
                    case beer: cout << "Cerveza " << atRestaurantOrder[n].RESTAURANT.quantitiesR[6] << " | "; break;
                    case soda: cout << "Soda " << atRestaurantOrder[n].RESTAURANT.quantitiesR[7] << " | "; break;
                    case tea: cout << "Te helado " << atRestaurantOrder[n].RESTAURANT.quantitiesR[8] << " | "; break;
                }

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
                cout << "\n\033[34mLA ORDEN HA SIDO DESPACHADA CON EXITO!.\033[0m\n";
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
                cout << "\n\033[34mLA ORDEN HA SIDO DESPACHADA CON EXITO!.\033[0m\n";
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

//FUNCION DEL TOTAL DE VENTAS
//total de ventas solo ordenes despachadas
void TotalSales(){
	//declaracion de variables
	stack<float> amountsIVA; //montos con IVA
	stack<float> Extra;  //para guardar los montos originales y no eliminarlos

	float AmountTop = 0, IVA = 0, AmountIVA = 0, totalSales = 0;
	
	while(!amounts.empty()){
		
		//se saca el primer monto de la pila
		AmountTop = amounts.top();
		
		//se le saca el iva al monto
		IVA = (AmountTop * 13) / 100;
		
		//se le agrega el iva
		AmountIVA = AmountTop + IVA;
		
		//se guarda el valor con iva en la pila de montos con iva
		amountsIVA.push(AmountIVA);
		
		//se guarda el valor original de la pila de montos sin iva en una pila temporal
		Extra.push(amounts.top());
		
		//se elimina temporalmente el monto de la pila amounts
		amounts.pop();
		
	}
	//se vuelve a llenar la pila original amounts
	while(!Extra.empty()){
		amounts.push(Extra.top());
		Extra.pop();
	}
	//se suman los montos con iva
	while(!amountsIVA.empty()){
		totalSales += amountsIVA.top();
		amountsIVA.pop();
	}
	cout << fixed << setprecision(2) << "\nVENTAS TOTALES: $" << totalSales << endl;
	totalSales = 0;
	
}

//FUNCION PARA CANCELAR UNA ORDEN
void CancelOrder(){
	
  //declaracion de variables
    bool orderFound = false, follow = true; 	
	string aName;
	int option = 0;

	if(isAdmin == false){
		cout << "\n\033[31mSOLO EL ADMINISTRADOR PUEDE CANCELAR UNA ORDEN!!\033[0m" << endl;
	}
	else{

		do{
			cout << "\nSELECCIONE EL TIPO DE ORDEN A CANCELAR:\n\n";
			cout << "1-Orden a domicilio | 2-Orden a restaurante | 3-Ninguna\n";
			cout << "Opcion: "; cin >> option; cin.ignore();

			switch(option){
				case 1:
					//cancelar orden a domicilio
					if(AnOrderDeliveryWasPlaced == false) cout << "\n\033[31mNO HAY NINGUNA ORDEN A DOMICILIO PARA CANCELAR!\033[0m" << endl;
					else{
						cout << "\nNombre del cliente de la orden a cancelar: "; getline(cin, aName);

						for(auto iter = atDeliveryOrder.begin(); iter != atDeliveryOrder.end(); ++iter){  
							if(iter->HOME.delivery.name == aName){
								orderFound = true;
								iter = atDeliveryOrder.erase(iter);
								cout << "\n\033[34mLA ORDEN HA SIDO CANCELADA!.\033[0m\n";
							break;
							}
						}
						if(orderFound == false){
							cout << "\n\033[31mNo hay ninguna orden al nombre de: " << aName << "\033[0m" << endl;
						}
						//si ya no hay ordenes en el vector original, la bandera que indica que hay una orden se vuelve false
						if(atDeliveryOrder.size() == 0){
							AnOrderDeliveryWasPlaced = false;
						}					
					}	
				break;
				case 2:
					//cancelar orden de restaurante
					if(AnOrderRestaurantWasPlaced == false) cout << "\n\033[31mNO HAY NINGUNA ORDEN A RESTAURANTE PARA CANCELAR!\033[0m" << endl;	
					else{
						//se pide nombre del cliente al cual se cancelara la orden
						cout << "\nNombre del cliente de la orden a cancelar: "; getline(cin, aName);
						for(auto iter = atRestaurantOrder.begin(); iter != atRestaurantOrder.end(); ++iter){  

							if(iter->RESTAURANT.Restaurant.name == aName){  
								orderFound = true;                  
								iter = atRestaurantOrder.erase(iter);
								cout << "\n\033[34mLA ORDEN HA SIDO CANCELADA!.\033[0m\n";
							break;
							}
						}
						if(orderFound == false){
							cout << "\n\033[31mNo hay ninguna orden al nombre de: " << aName << "\033[0m" << endl;
						}
						//si ya no hay ordenes en el vector original, la bandera que indica que hay una orden se vuelve false
						if(atRestaurantOrder.size() == 0){
							AnOrderRestaurantWasPlaced = false;
						}					
					}
				break;
				case 3: follow = false; break;
				default: cout << "Opcion invalida!" << endl;
			}
		}while(follow);

	}

}

//FUNCIONES DE TIEMPO DE ESPERA

//funcion ver tiempo de espera de ordenes a domicilio
void WaitTimeDelibery(int i, float TotalTimeOuts){
	//declaracion de variables
	float TotalTime = 0, starterT = 0, maindishT = 0, drinkT = 0;

	if(AnOrderDeliveryWasPlaced == false){
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(i == 0) cout << endl; //para que haya un espacio en la primera iteracion

		if(i == atDeliveryOrder.size()){
			
			cout << "\033[34mTotal del tiempo de espera: " << fixed << setprecision(0) << TotalTimeOuts << " minutos\033[0m" << endl;
			cout << fixed << setprecision(2);
			cout << "\nSe ha mostrado el tiempo de espera de cada orden a domicilio!" << endl;

		}
		else{
			//sumando los totales de entradas, platos principales y bebidas de la orden		
			starterT = (atDeliveryOrder[i].HOME.quantitiesD[0] + atDeliveryOrder[i].HOME.quantitiesD[1]+ atDeliveryOrder[i].HOME.quantitiesD[2]);
			maindishT = (atDeliveryOrder[i].HOME.quantitiesD[3] + atDeliveryOrder[i].HOME.quantitiesD[4]+ atDeliveryOrder[i].HOME.quantitiesD[5]);
			drinkT = (atDeliveryOrder[i].HOME.quantitiesD[6] + atDeliveryOrder[i].HOME.quantitiesD[7]+ atDeliveryOrder[i].HOME.quantitiesD[8]);

			//tiempo total de espera de la orden
			TotalTime = (starterT * 1.10 + maindishT * 1.5 + drinkT * 1.35) + 15;

			cout << "ORDEN " << atDeliveryOrder[i].HOME.idOrderDelivery << " | ";
			cout << "Cliente: " << atDeliveryOrder[i].HOME.delivery.name << " | ";
			cout << "Monto de la orden: $" << atDeliveryOrder[i].HOME.TotalamountDelivery << " | ";
			cout << "Tiempo de espera: " << fixed << setprecision(0) << "\033[34m" << TotalTime << " minutos\n\033[0m";
			TotalTimeOuts += TotalTime;
			cout << fixed << setprecision(2); 
			i++;
		
			WaitTimeDelibery(i, TotalTimeOuts);
			
		}	
		
	}

}

//funcion ver tiempo de espera de ordenes a restaurante
void WaitTimeRestaurant(int i, float TotalTimeOuts){
	//declaracion de variables
	float TotalTime = 0, starterT = 0, maindishT = 0, drinkT = 0;

	if(AnOrderRestaurantWasPlaced == false){
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(i == 0) cout << endl; //para que haya un espacio en la primera iteracion

		if(i == atRestaurantOrder.size()){
			cout << "\033[34mTotal del tiempo de espera: " << fixed << setprecision(0) << TotalTimeOuts << " minutos\033[0m" << endl;
			cout << fixed << setprecision(2);
			cout << "\nSe ha mostrado el tiempo de espera de cada orden a restaurante!" << endl;

		}
		else{
			//sumando los totales de entradas, platos principales y bebidas de la orden		
			starterT = (atRestaurantOrder[i].RESTAURANT.quantitiesR[0] + atRestaurantOrder[i].RESTAURANT.quantitiesR[1]+ atRestaurantOrder[i].RESTAURANT.quantitiesR[2]);
			maindishT = (atRestaurantOrder[i].RESTAURANT.quantitiesR[3] + atRestaurantOrder[i].RESTAURANT.quantitiesR[4]+ atRestaurantOrder[i].RESTAURANT.quantitiesR[5]);
			drinkT = (atRestaurantOrder[i].RESTAURANT.quantitiesR[6] + atRestaurantOrder[i].RESTAURANT.quantitiesR[7]+ atRestaurantOrder[i].RESTAURANT.quantitiesR[8]);

			//tiempo total de espera de la orden
			TotalTime = (starterT * 1.10 + maindishT * 1.5 + drinkT * 1.35);

			cout << "ORDEN " << atRestaurantOrder[i].RESTAURANT.idOderRestaurant << " | ";
			cout << "Cliente: " << atRestaurantOrder[i].RESTAURANT.Restaurant.name << " | ";
			cout << "Monto de la orden: $" << atRestaurantOrder[i].RESTAURANT.TotalamountRestaurant << " | ";
			cout << "Tiempo de espera: " << fixed << setprecision(0) << "\033[34m" << TotalTime << " minutos\n\033[0m";
			TotalTimeOuts += TotalTime;
			cout << fixed << setprecision(2);
			i++;
		
			WaitTimeRestaurant(i, TotalTimeOuts);
			
		}	
		
	}
}