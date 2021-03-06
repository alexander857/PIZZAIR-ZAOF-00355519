#include<iostream>
#include<string>
#include<iomanip> //para la funcion redondear decimales
#include <vector>

//contraseña del sistema
#define PASSWORD "delete"
#define __Color_h__ //cambia color de las letras

using namespace std;

//ENUMERACIONES
//enumeraciones de los menus de comida
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
    starter pStarter[3]; //donde se guardan las opciones de entradas
    mainDish pDish[3];   //donde se guardan las opciones de platos principales
    drink pDrink[3];	  //donde se guardan las opciones de bebidas
    paymentType pay;
	float price;
	int id, quantitiesSPD[3], quantities[9]; //cantidad de entradas platos y bebidas
};

//pedidos a domicilio
struct DeliveryOrders{	

	CustomerAddress Address;
	string phone;
	mainData delivery;
	float TotalamountDelivery, timeD;
		
};

//pedidos a restaurante
struct RestaurantOrders{
	
	int PeoplePerTable;
	mainData Restaurant;
	float TotalamountRestaurant, timeR;
	
};

//una orden
struct AnOrder{
	
	DeliveryOrders HOME;
	RestaurantOrders RESTAURANT;
	
};

typedef struct AnOrder ANORDER; //variable para acceder a los registros

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

//PROTOTIPOS DE LAS FUNCIONES
bool LogIn(), PizzaMenu(); 
void AddOrder(), AddOrder(int), SeeDeliveryOrder(int), SeeRestaurantOrder(int), DispatchDeliveryOrder(), DispatchRestauranOrder();
void WaitTimeDelibery(int, float), WaitTimeRestaurant(int, float), CancelOrder(), TotalSales();


int main(){

	 LogIn(); //se llama la funcion de inicio de sesion
	 
	 PizzaMenu(); //menu principal de la pizzeria
	
	return 0;
}

//menu principal del sistema de despacho
bool PizzaMenu(){
	//variables de la funcion
	bool follow = true;	
	
	do{
		int option = 0;
		//nombre de la pizzeria
		cout << "\n\033[36mMENU PRINCIPAL PIZZAIR\033[0m" << endl;
		
		//menu de opciones
		
		cout << "\n1-Agregar orden a domicilio\n";
		cout << "2-Agregar orden en restaurante\n";
		cout << "3-Ver ordenes a domicilio\n";
		cout << "4-Ver ordenes en restaurante\n";
		cout << "5-Despachar ordenes a domicilio\n";
		cout << "6-Despachar ordenes en restaurante\n";
		cout << "7-Ver tiempo promedio de espera domicilio\n";
		cout << "8-Ver tiempo promedio de espera restaurante\n";
		cout << "9-Cancelar orden (domicilio o restaurante, \033[31msolo Admin\033[0m)\n";
		cout << "10-Calcular total de ventas\n";
		cout << "11-Cambiar de usuario\n";
		cout << "12-Salir\n";
		cout << "\nOpcion: "; cin >> option;
		cin.ignore();
		
		
		switch(option){
			//funciones llamadas al menu
			case 1: AddOrder(); break;      //pedir orden a domicilio
			case 2: AddOrder(0); break;		//pedir orden a restaurante
			case 3: SeeDeliveryOrder(0); break;   //ver las ordenes a domicilio
			case 4: SeeRestaurantOrder(0); break;  //ver las ordenes a restaurante
			case 5: DispatchDeliveryOrder(); break;  //despachar ordenes a domicilio
			case 6: DispatchRestauranOrder(); break;  //despachar ordenes a restaurante
			case 7: WaitTimeDelibery(0, 0); break;   //tiempo de espera de las ordenes a domicilio
			case 8: WaitTimeRestaurant(0, 0); break; //tiempo de espera de las ordenes a restaurante
			case 9: CancelOrder(); break;  //cancelar una orden
			case 10: TotalSales(); break;   //ver total de las ventas
			case 11: LogIn(); break;      //cambiar de usuario
			case 12: follow = false; break;
			default: cout << "\n\033[31mOPCION NO VALIDA!\033[0m\n"; break;
			
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
					
					if(key.compare(PASSWORD) == 0){ //se verifica si la clave es correcta
						
						cout << "\n\033[33mHAS INICIADO SESION COMO ADMINISTRADOR!\033[0m" << endl;
						isAdmin = true; //verifica que se inicio sesion como admin
						k = 1;
					}			
				}
				break;	
				
			case '2':
				cout << "\n\033[33mHAS INICIADO SESION COMO EMPLEADO!\033[0m" << endl;
				isAdmin = false; //si se inicia sesion como empleado se vuelve falsa
				k = 1;
				break;
			default :
				cout << "\n\033[31mOPCION NO VALIDA!\033[0m" << endl;
				
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
		anorder.HOME.delivery.quantities[i] = 0;
	}
	//inicializando contador de entradas, platos principales y bebidas
	for(int i = 0; i < 3; i++){
		anorder.HOME.delivery.quantitiesSPD[i] = 0;
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
            case 1: anorder.HOME.delivery.pStarter[0] = garlicBread; //se guarda la primera opcion
            		anorder.HOME.delivery.price += 3.99;     //se guarda el precio de esa opcion
					anorder.HOME.delivery.quantities[0] += 1;  //aumenta la variable que lleva el numero de veces que se eligio
					requested = true; break;  //verifica si algo se ingreso a la orden
            case 2: anorder.HOME.delivery.pStarter[1] = pizzaRolls;  //se guarda la segunda opcion
					anorder.HOME.delivery.price += 4.99; 
					anorder.HOME.delivery.quantities[1] += 1;
					requested = true; break;
            case 3: anorder.HOME.delivery.pStarter[2] = cheeseSticks; //se guarda la tercera opcion
					anorder.HOME.delivery.price += 3.75; 
					anorder.HOME.delivery.quantities[2] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
		anorder.HOME.delivery.quantitiesSPD[0] += 1; //contador de numero de entradas
    }while(follow);
	
	follow = true;
    do{
    
	  	cout << "\nPLATO PRINCIPAL:\n";
		cout << "\n1-Pizza | 2-Pasta | 3-Lasagna | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pDish[0] = pizza; 
            		anorder.HOME.delivery.price += 13.99; 
					anorder.HOME.delivery.quantities[3] += 1;
					requested = true; break; //verifica si se pidio algo
            case 2: anorder.HOME.delivery.pDish[1] = pasta;				
					anorder.HOME.delivery.price += 5.55; 
					anorder.HOME.delivery.quantities[4] += 1;
					requested = true; break;
            case 3: anorder.HOME.delivery.pDish[2] = lasagna; 
					anorder.HOME.delivery.price += 6.25; 
					anorder.HOME.delivery.quantities[5] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
		anorder.HOME.delivery.quantitiesSPD[1] += 1; //contador de platos principales
    }while(follow);

	follow = true;
    do{

	  	cout << "\nBEBIDA:\n";
		cout << "\n1-Cerveza | 2-Soda | 3-Te helado | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.HOME.delivery.pDrink[0] = beer;
            		anorder.HOME.delivery.price += 1.99; 
					anorder.HOME.delivery.quantities[6] += 1;
					requested = true; break; //verifica si se pidio algo
            case 2: anorder.HOME.delivery.pDrink[1] = soda;			
					anorder.HOME.delivery.price += 0.95; 
					anorder.HOME.delivery.quantities[7] += 1;
					requested = true; break;
            case 3: anorder.HOME.delivery.pDrink[2] = tea;
					anorder.HOME.delivery.price += 1.15; 
					anorder.HOME.delivery.quantities[8] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
		anorder.HOME.delivery.quantitiesSPD[2] += 1; //contador de bebidas
    }while(follow);
	
	//guardando el monto total de la orden
	anorder.HOME.TotalamountDelivery = anorder.HOME.delivery.price;

    //calculando el tiempo de espera de la orden segun las entradas, platos principales y bebidas
    anorder.HOME.timeD += (anorder.HOME.delivery.quantitiesSPD[0]-1) * 1.10;
    anorder.HOME.timeD += (anorder.HOME.delivery.quantitiesSPD[1]-1) * 1.5;
    anorder.HOME.timeD += (anorder.HOME.delivery.quantitiesSPD[2]-1) * 1.35;
    anorder.HOME.timeD += 15;

    follow = true;
	if(requested == true){ //entra a esta condicion si hay algo en la orden

		do{
			//se pide el tipo de pago
			cout << "\nTipo de pago:\n";
			cout << "\n1-Efectivo | 2-Tarjeta\n";
			cout << "Opcion: "; cin >> option;
			switch(option){
				case 1: anorder.HOME.delivery.pay = cash; follow = false; break;
				case 2: anorder.HOME.delivery.pay = card; follow = false; break;			
				default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
			}
		}while(follow);
		//se muestra el monto de la orden
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
		anorder.RESTAURANT.Restaurant.quantities[i] = 0;
	}
	//inicializando el contador de entradas, platos principales y bebidas
	for(int i = 0; i < 3; i++){
		anorder.RESTAURANT.Restaurant.quantitiesSPD[i] = 0;
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
            case 1: anorder.RESTAURANT.Restaurant.pStarter[0] =  garlicBread; //se guarda la primera opcion
            		anorder.RESTAURANT.Restaurant.price += 3.99;   //se guarda el precio
					anorder.RESTAURANT.Restaurant.quantities[0] += 1;  //la cantidad de esa opcion
					requested = true; break; //verifica si se ingreso algo
            case 2: anorder.RESTAURANT.Restaurant.pStarter[1] = pizzaRolls; //se guarda la segunda opcion
					anorder.RESTAURANT.Restaurant.price += 4.99; 
					anorder.RESTAURANT.Restaurant.quantities[1] += 1; 
					requested = true; break;
            case 3: anorder.RESTAURANT.Restaurant.pStarter[2] = cheeseSticks;  //se guarda la tercera opcion
					anorder.RESTAURANT.Restaurant.price += 3.75; 
					anorder.RESTAURANT.Restaurant.quantities[2] += 1;
					requested = true; break; 
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
		anorder.RESTAURANT.Restaurant.quantitiesSPD[0] += 1; //cantidad de entradas
    }while(follow);
	
	follow = true;
    do{
    
	  	cout << "\nPLATO PRINCIPAL:\n";
		cout << "\n1-Pizza | 2-Pasta | 3-Lasagna | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pDish[0] = pizza; 
            		anorder.RESTAURANT.Restaurant.price += 13.99; 
					anorder.RESTAURANT.Restaurant.quantities[3] += 1;
					requested = true; break;
            case 2: anorder.RESTAURANT.Restaurant.pDish[1] = pasta; 				
					anorder.RESTAURANT.Restaurant.price += 5.55; 
					anorder.RESTAURANT.Restaurant.quantities[4] += 1;
					requested = true; break;
            case 3: anorder.RESTAURANT.Restaurant.pDish[2] = lasagna; 
					anorder.RESTAURANT.Restaurant.price += 6.25; 
					anorder.RESTAURANT.Restaurant.quantities[5] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
		anorder.RESTAURANT.Restaurant.quantitiesSPD[1] += 1; //cantidad de platos principales
    }while(follow);
	
	follow = true;
    do{
    
	  	cout << "\nBEBIDA:\n";
		cout << "\n1-Cerveza | 2-Soda | 3-Te helado | 4-Siguiente menu...\n";
		cout << "Opcion: "; cin >> option;
        switch(option){
            case 1: anorder.RESTAURANT.Restaurant.pDrink[0] = beer;
            		anorder.RESTAURANT.Restaurant.price += 1.99; 
					anorder.RESTAURANT.Restaurant.quantities[6] += 1;
					requested = true; break;
            case 2: anorder.RESTAURANT.Restaurant.pDrink[1] = soda; 				
					anorder.RESTAURANT.Restaurant.price += 0.95; 
					anorder.RESTAURANT.Restaurant.quantities[7] += 1;
					requested = true; break;
            case 3: anorder.RESTAURANT.Restaurant.pDrink[2] = tea; 	
					anorder.RESTAURANT.Restaurant.price += 1.15; 
					anorder.RESTAURANT.Restaurant.quantities[8] += 1;
					requested = true; break;
            case 4:follow = false; break;
            default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
        }
		anorder.RESTAURANT.Restaurant.quantitiesSPD[2] += 1; //cantidad de bebidas
    }while(follow);
	
    //guardando el monto de la orden
	anorder.RESTAURANT.TotalamountRestaurant = anorder.RESTAURANT.Restaurant.price;

    //calculando el tiempo de espera de la orden segun las entradas, platos principales y bebidas
    anorder.RESTAURANT.timeR += (anorder.RESTAURANT.Restaurant.quantitiesSPD[0]-1) * 1.10;
    anorder.RESTAURANT.timeR += (anorder.RESTAURANT.Restaurant.quantitiesSPD[1]-1) * 1.5;
    anorder.RESTAURANT.timeR += (anorder.RESTAURANT.Restaurant.quantitiesSPD[2]-1) * 1.35;

    follow = true;
	if(requested == true){ //si se ingreso algo a la orden entra e la condicio

		do{
			//se pide el tipo de pago
			cout << "\nTipo de pago:\n";
			cout << "\n1-Efectivo | 2-Tarjeta\n";
			cout << "Opcion: "; cin >> option;
			switch(option){
				case 1: anorder.RESTAURANT.Restaurant.pay = cash; follow = false; break;
				case 2: anorder.RESTAURANT.Restaurant.pay = card; follow = false; break;			
				default: cout << "\n\033[31mOpcion erronea!\033[0m" << endl; break;
			}
		}while(follow);
		//se muestra el monto de la orden
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
	

	if(AnOrderDeliveryWasPlaced == false){ //si no se ha ingresado ninguna orden
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(i == atDeliveryOrder.size()){ //caso base de la recursion
			
			cout << "\nSE HAN MOSTRADO TODAS LAS ORDENES A DOMICILIO!" << endl;

		}
		else{		
			//se muestra la informacion de la orden
			cout << "\n\033[34mORDEN " << atDeliveryOrder[i].HOME.delivery.id << "\033[0m\n" << endl;
			cout << "Nombre del cliente: " << atDeliveryOrder[i].HOME.delivery.name << endl;
			cout << "Direccion: ";
			cout << "No.Casa: " << atDeliveryOrder[i].HOME.Address.HouseNumber << ", ";
			cout << atDeliveryOrder[i].HOME.Address.Suburb << ", ";
			cout << atDeliveryOrder[i].HOME.Address.Municipality << ", ";
			cout << atDeliveryOrder[i].HOME.Address.State << endl;
			cout << "Telefono: " << atDeliveryOrder[i].HOME.phone << endl;

            //switch donde se muestran los platos y bebidas ordenados y cuantos de cada uno
 			cout << "\n\033[32mEntrada: \033[0m";
             for(int j = 0; j < 3; j++){

                switch(atDeliveryOrder[i].HOME.delivery.pStarter[j]){
                    case garlicBread: cout << "Pan con ajo " << atDeliveryOrder[i].HOME.delivery.quantities[0] << " | "; break;
                    case pizzaRolls: cout << "Pizza rolls " << atDeliveryOrder[i].HOME.delivery.quantities[1] << " | "; break;
                    case cheeseSticks: cout << "Palitos de queso " << atDeliveryOrder[i].HOME.delivery.quantities[2] << " | "; break;
                }

             }
            //se muestran los platos principales de la orden 
            cout << "\n\033[35mPlato principal: \033[0m";
            for(int j = 0; j < 3; j++){

                switch(atDeliveryOrder[i].HOME.delivery.pDish[j]){ 
                    case pizza: cout << "Pizza " << atDeliveryOrder[i].HOME.delivery.quantities[3] << " | "; break;
                    case pasta: cout << "Pasta " << atDeliveryOrder[i].HOME.delivery.quantities[4] << " | "; break;
                    case lasagna: cout << "Lasagna " << atDeliveryOrder[i].HOME.delivery.quantities[5] << " | "; break;
                }

            }
            //se muestran las bebidas de la orden
            cout << "\n\033[36mBebida: \033[0m";
            for(int j = 0; j < 3; j++){

                switch( atDeliveryOrder[i].HOME.delivery.pDrink[j]){
                    case beer: cout << "Cerveza " << atDeliveryOrder[i].HOME.delivery.quantities[6] << " | "; break;
                    case soda: cout << "Soda " << atDeliveryOrder[i].HOME.delivery.quantities[7] << " | "; break;
                    case tea: cout << "Te helado " << atDeliveryOrder[i].HOME.delivery.quantities[8] << " | "; break; 
                }

            }
            //se muestra el tipo de pago de la orden
            cout << "\n\nTipo de pago: ";
             switch( atDeliveryOrder[i].HOME.delivery.pay){
                case cash: cout << "Efectivo" << endl; break;
                case card: cout << "Tarjeta" << endl; break;
            }
			cout << "Monto de la orden: $" << atDeliveryOrder[i].HOME.TotalamountDelivery << endl;
			cout << "Tiempo de espera de la orden: " << fixed << setprecision(0) << atDeliveryOrder[i].HOME.timeD << " minutos" << endl;
			cout << fixed << setprecision(2); //se vuelve a ocupar esta funcion para que no redondee todas las demas cantidades del programa

			i++; //aumenta el iterador para ir recorriendo el vector de las ordenes
		
			SeeDeliveryOrder(i); //llamada recursiva
			
		}	
		
	}

}

//ver ordenes a restaurante
void SeeRestaurantOrder(int n){
	

	if(AnOrderRestaurantWasPlaced == false){ //si no hay ordenes 
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(n == atRestaurantOrder.size()){ //caso base de la recursion
			
			cout << "\nSE HAN MOSTRADO TODAS LAS ORDENES A RESTAURANTE!" << endl;

		}
		else{		
			//se muestran los datos de la orden	
			cout << "\n\033[34mORDEN " << atRestaurantOrder[n].RESTAURANT.Restaurant.id << "\033[m\n" << endl;
			cout << "Nombre del cliente: " << atRestaurantOrder[n].RESTAURANT.Restaurant.name << endl;
			cout << "Personas por mesa: " << atRestaurantOrder[n].RESTAURANT.PeoplePerTable << endl;

            //switch donde se muestran todos los platos y bebidas de la orden y cuantos de cada uno
			cout << "\n\033[32mEntrada: \033[0m";
            for(int i = 0; i < 3; i++){

                switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pStarter[i]){
                    case garlicBread: cout << "Pan con ajo " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[0] << " | "; break;
                    case pizzaRolls: cout << "Pizza rolls " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[1] << " | "; break;
                    case cheeseSticks: cout << "Palitos de queso " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[2] << " | "; break;
                }

            }
			//se muestran los platos principales de la orden
            cout << "\n\033[35mPlato principal: \033[0m";
            for(int i = 0; i < 3; i++){

                switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDish[i]){
                    case pizza: cout << "Pizza " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[3] << " | "; break;
                    case pasta: cout << "Pasta " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[4] << " | "; break;
                    case lasagna: cout << "Lasagna " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[5] << " | "; break;
                }

            }
			//se muestran las bebidas seleccionadas en la orden
            cout << "\n\033[36mBebida: \033[0m";
            for(int i = 0; i < 3; i++){

                switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pDrink[i]){
                    case beer: cout << "Cerveza " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[6] << " | "; break;
                    case soda: cout << "Soda " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[7] << " | "; break;
                    case tea: cout << "Te helado " << atRestaurantOrder[n].RESTAURANT.Restaurant.quantities[8] << " | "; break;
                }

            }
			//se muestra el tipo de pago
            cout << "\n\nTipo de pago: ";
            switch(atRestaurantOrder[n].RESTAURANT.Restaurant.pay){
                case cash: cout << "Efectivo" << endl; break;
                case card: cout << "Tarjeta" << endl; break;
            }
			cout << "Monto de la orden: $" << atRestaurantOrder[n].RESTAURANT.TotalamountRestaurant << endl;
			cout << "Tiempo de espera de la orden: " << fixed << setprecision(0) << atRestaurantOrder[n].RESTAURANT.timeR << " minutos" << endl;
			cout << fixed << setprecision(2);//se vuelve a ocupar esta funcion para que no redondee todas las demas cantidades del programa
			
			n++; //interador para recorrer el vector de las ordenes
			
			SeeRestaurantOrder(n); //llamada recursiva
			
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
	
	if(AnOrderDeliveryWasPlaced == false){ //si no hay ordenes
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN PARA DESPACHAR!\033[0m" << endl;
		
	}
	else{ //se pide el nombre del cliente a despachar
        cout << "\nNombre del cliente a despachar: "; getline(cin, aName);
		//se busca en un for si la orden esta
        for(auto iter = atDeliveryOrder.begin(); iter != atDeliveryOrder.end(); ++iter){  
            if(iter->HOME.delivery.name == aName){ //entra a este if si se encuentra la orden
                if(k > 0){ //si en la primera posicion no se encontro la orden
                    cout << "\nHay alguien antes de " << aName << ", despache primero a " << atDeliveryOrder[i].HOME.delivery.name << endl;
                    orderFound = true;
                    break;
                }
                orderFound = true; //verifica que la orden se encontro y se despacha
                DispatchHome.insert(DispatchHome.end(), atDeliveryOrder[i]);
                iter = atDeliveryOrder.erase(iter);
                cout << "\n\033[34mLA ORDEN HA SIDO DESPACHADA CON EXITO!.\033[0m\n";
            break;
            }
            else
                k++; //aumenta si en la primera posicion no se encontro la orden

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
	
	if(AnOrderRestaurantWasPlaced == false){ //si no hay ordenes
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN PARA DESPACHAR!\033[0m" << endl;
		
	}
	else{//se pide nombre del cliente
        cout << "\nNombre del cliente a despachar: "; getline(cin, aName);
		//se busca la orden en el for
        for(auto iter = atRestaurantOrder.begin(); iter != atRestaurantOrder.end(); ++iter){  
			//si la orden se encuentra entra al if
            if(iter->RESTAURANT.Restaurant.name == aName){  
                 if(k > 0){ //si no se encontro en la primera iteracion entra a esta condicion
                    cout << "\nHay alguien antes de " << aName << ", despache primero a " << atRestaurantOrder[i].RESTAURANT.Restaurant.name << endl;
                    orderFound = true;
                    break;
                }
                orderFound = true; //verifica que se encontro la orden y se despacha 
                DispatchRestaurant.insert(DispatchRestaurant.end(), atRestaurantOrder[i]);
                iter = atRestaurantOrder.erase(iter);
                cout << "\n\033[34mLA ORDEN HA SIDO DESPACHADA CON EXITO!.\033[0m\n";
            break;
            }
            else
                k++; //si no se encontro en la primera iteracion aumenta k
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
    float IVA = 0, amountIVAD = 0, amountIVAR = 0;

    //sacando montos con iva de ordenes a domicilio
    for(int i = 0; i < DispatchHome.size(); i++){
        IVA = (DispatchHome[i].HOME.TotalamountDelivery * 13) / 100; //se saca el iva al monto
        amountIVAD += DispatchHome[i].HOME.TotalamountDelivery + IVA; //se le agrega el iva al monto
    }

    //sacando montos con iva de ordenes a restaurante
    for(int i = 0; i < DispatchRestaurant.size(); i++){
        IVA = (DispatchRestaurant[i].RESTAURANT.TotalamountRestaurant * 13) / 100;//se saca el iva del monto
        amountIVAR += DispatchRestaurant[i].RESTAURANT.TotalamountRestaurant + IVA; //se le agrega el iva al monto
    }
    //se muestra el total de las ventas
    cout << "\nTOTAL DE VENTAS: $" << fixed << setprecision(2) << amountIVAD + amountIVAR << endl; 

}


//FUNCION PARA CANCELAR UNA ORDEN
void CancelOrder(){
	
  //declaracion de variables
    bool orderFound = false, follow = true; 	
	string aName;
	int option = 0;

	if(isAdmin == false){ //se verifica si se ha ingresado como admin o no
		cout << "\n\033[31mSOLO EL ADMINISTRADOR PUEDE CANCELAR UNA ORDEN!!\033[0m" << endl;
	}
	else{
		//se elige que tipo de orden se cancelara
		do{
			cout << "\nSELECCIONE EL TIPO DE ORDEN A CANCELAR:\n\n";
			cout << "1-Orden a domicilio | 2-Orden a restaurante | 3-Ninguna\n";
			cout << "Opcion: "; cin >> option; cin.ignore();

			switch(option){
				case 1:
					//cancelar orden a domicilio
					if(AnOrderDeliveryWasPlaced == false) cout << "\n\033[31mNO HAY NINGUNA ORDEN A DOMICILIO PARA CANCELAR!\033[0m" << endl;
					else{//se pide nombre del cliente a cancelar
						cout << "\nNombre del cliente de la orden a cancelar: "; getline(cin, aName);
						//se busca en el vector si la orden se encuentra para cancelar
						for(auto iter = atDeliveryOrder.begin(); iter != atDeliveryOrder.end(); ++iter){  
							if(iter->HOME.delivery.name == aName){
								orderFound = true; //verifica que la orden fue encontrada
								iter = atDeliveryOrder.erase(iter);
								cout << "\n\033[34mLA ORDEN HA SIDO CANCELADA!.\033[0m\n";
							break;
							}
						}
						if(orderFound == false){ //si la orden no se encontro
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
						//se busca en el vector si la orden se encuentra para cancelar
						for(auto iter = atRestaurantOrder.begin(); iter != atRestaurantOrder.end(); ++iter){  

							if(iter->RESTAURANT.Restaurant.name == aName){  
								orderFound = true;   //verifica que la orden fue encontrada                
								iter = atRestaurantOrder.erase(iter);
								cout << "\n\033[34mLA ORDEN HA SIDO CANCELADA!.\033[0m\n";
							break;
							}
						}
						if(orderFound == false){ //si la orden no se encontro
							cout << "\n\033[31mNo hay ninguna orden al nombre de: " << aName << "\033[0m" << endl;
						}
						//si ya no hay ordenes en el vector original, la bandera que indica que hay una orden se vuelve false
						if(atRestaurantOrder.size() == 0){
							AnOrderRestaurantWasPlaced = false;
						}					
					}
				break;
				case 3: follow = false; break;
				default: cout << "\n\033[31mOpcion invalida!\033[0m" << endl;
			}
		}while(follow);

	}

}

//FUNCIONES DE TIEMPO DE ESPERA

//funcion ver tiempo de espera de ordenes a domicilio
void WaitTimeDelibery(int i, float TotalTimeOuts){
	//declaracion de variables
	float TotalTime = 0;

	if(AnOrderDeliveryWasPlaced == false){ //si no hay ninguna orden
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(i == 0) cout << endl; //para que haya un espacio en la primera iteracion

		if(i == atDeliveryOrder.size()){ //caso base de la recursion
			
			cout << "\033[34mTotal del tiempo de espera: " << fixed << setprecision(0) << TotalTimeOuts << " minutos\033[0m" << endl;
			cout << fixed << setprecision(2);
			cout << "\nSe ha mostrado el tiempo de espera de cada orden a domicilio!" << endl;

		}
		else{

			//tiempo total de espera de la orden
			TotalTime = atDeliveryOrder[i].HOME.timeD;

			cout << "ORDEN " << atDeliveryOrder[i].HOME.delivery.id << " | ";
			cout << "Cliente: " << atDeliveryOrder[i].HOME.delivery.name << " | ";
			cout << "Monto de la orden: $" << atDeliveryOrder[i].HOME.TotalamountDelivery << " | ";
			cout << "Tiempo de espera: " << fixed << setprecision(0) << "\033[34m" << TotalTime << " minutos\n\033[0m";
			TotalTimeOuts += TotalTime;
			cout << fixed << setprecision(2); //se vueve a pone esta funcion para que los demas montos del programa sigan normal
			i++;
		
			WaitTimeDelibery(i, TotalTimeOuts); //llamada recursiva
			
		}	
		
	}

}

//funcion ver tiempo de espera de ordenes a restaurante
void WaitTimeRestaurant(int i, float TotalTimeOuts){
	//declaracion de variables
	float TotalTime = 0;

	if(AnOrderRestaurantWasPlaced == false){ //si no hay ordenes
		
		cout << "\n\033[31mNO HAY NINGUNA ORDEN!\033[0m" << endl;
		
	}
	else{
		
		if(i == 0) cout << endl; //para que haya un espacio en la primera iteracion

		if(i == atRestaurantOrder.size()){ //caso base de la recursion
			cout << "\033[34mTotal del tiempo de espera: " << fixed << setprecision(0) << TotalTimeOuts << " minutos\033[0m" << endl;
			cout << fixed << setprecision(2);
			cout << "\nSe ha mostrado el tiempo de espera de cada orden a restaurante!" << endl;

		}
		else{

			//tiempo total de espera de la orden
			TotalTime = atRestaurantOrder[i].RESTAURANT.timeR;

			cout << "ORDEN " << atRestaurantOrder[i].RESTAURANT.Restaurant.id << " | ";
			cout << "Cliente: " << atRestaurantOrder[i].RESTAURANT.Restaurant.name << " | ";
			cout << "Monto de la orden: $" << atRestaurantOrder[i].RESTAURANT.TotalamountRestaurant << " | ";
			cout << "Tiempo de espera: " << fixed << setprecision(0) << "\033[34m" << TotalTime << " minutos\n\033[0m";
			TotalTimeOuts += TotalTime;
			cout << fixed << setprecision(2);//se vueve a pone esta funcion para que los demas montos del programa sigan normal
			i++;
		
			WaitTimeRestaurant(i, TotalTimeOuts); //llamada recursiva
			
		}		
	}
}