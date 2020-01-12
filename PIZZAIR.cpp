#include<iostream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

using namespace std;

//PROTOTIPOS DE LAS FUNCIONES
//funcion de menu principal
char PizzaMenu();

//funciones de pedidos
void HomeOrders(char name[10], char&, float&,int&,int&,int&); //pedidos a domicilio
void CustomInRestaurant( char name[10], char&, float&,int&,int&,int&);//pedidos a restaurante
void FoodAmountPayment(char&,float&,int&,int&,int&); //se selecciona la comida, el tipo de pago y el monto

//funciones de menus de comidas
int PrincipalFood(int&);
int FoodTickets(int&);
int Drinks(int&);

//funciones de archivos donde se guardan los pedidos
void HomeOrderFile(char name[10], char&,float&, string address, string phone,int&,int&,int&); //archivo de pedidos a domicilio
void OrderFileToRestaurant(char name[10], char&, float& ,int&,int&,int&,int&); //archivo de encargos a restaurante

//funciones que leen los archivos de los pedidos a domicilio y restaurante
void ReadHomeOrders();

//otras funciones 
string DateFunction();

int main(){
	//DECLARACION DE VARIABLES 
	//contrase?a para el menu principal
	char password[]="delete", key[6], PaymentType, name[10], option;  
	int k = 0, A = 0, B = 0, C = 0;
	float amount = 0; 	
	
	//pedimos la contrase?a para ingresar
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout<<"Ingrese la clave: ";cin>>key;
	
	//hay solo 3 intentos para ingresar la contrase?a correcta
	while(k==0){
		
		//se compara si la contrase?a es correcta
		if(strcmp(password,key) == 0){ //compara las dos palabras: password y key 
			
			system("cls"); 
			option = PizzaMenu(); //se llama la funcion del menu principal si la contraseñña es correcta
			system("cls");
			
			//condiciones segun lo que se seleccione en el menu principal
			if(option == '1'){
				
				HomeOrders(name,PaymentType,amount,A,B,C); //se llama a la funcion para agregar un pedido a domicilio
				
			}
			else if(option == '2'){
				cout<<"No disponible"<<endl;
				system("pause");
				system("cls");
			}
			else if(option == '3'){
				
				ReadHomeOrders(); //se llama la funcion que lee el archivo de pedidos a domicilio
				//system("pause");
				
			}
			else if(option == '4'){
				cout<<"No disponible"<<endl;
				system("pause");
				system("cls");
			}
			else if(option == '5'){
				cout<<"No disponible"<<endl;
				system("pause");
				system("cls");
			}						
		
		}
		
		else{     //si no son iguaes las palabras, le sigue pidiendo que ingrese la clave hasta que ingrese la correcta
			
			system("cls");
			cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
			cout<<"Ingrese la clave: ";cin>>key;
			
		}	
						
	}
	
	return 0;
}

//menu principal del sistema de despacho
char PizzaMenu(){
	//variables de la funcion
	char option;
	
	//nosbre de la pizzaria
	cout<<"PIZZAIR\n"<<endl;
	
	//menu de opciones
	cout<<"1-Agregar 1 pedido a domicilio\n2-Agregar 1 encargo en restaurante\n3-Ver pedidos a domicilio\n4-Ver encargos en restaurante\n5-Ver total de ventas\n"<<endl;
	
	//se pide una opcion a seleccionar
	cout<<"Opcion: ";cin>>option;
	
	return option;
}

//FUNCIONES PARA LOS PEDIDOS

//funcion de pedidos a domicilio
void HomeOrders(char name[10], char& PaymentType, float& amount,int&A,int&B,int&C){
	//variables de la funcion
	string address, phone;
	
	//se pide la informacion del pedido
	cout<<"Nombre del cliente: ";cin>>name;
	
	cout<<"Direccion: ";cin>>address;
	
	cout<<"Telefono: ";cin>>phone;
	system("cls");
	
	FoodAmountPayment(PaymentType,amount,A,B,C);  //se llama a la funcion donde se eligen los platos de comida, el monto y tipo de pago
	HomeOrderFile(name,PaymentType,amount,address,phone,A,B,C); //se llama a la funcion que crea el archivo donde se guardan todos los datos de la orden a domicilio
	
	
}

//funcion de pedidos a restaurante
void CustomInRestaurant(char name[10], char& PaymentType, float& amount,int&A,int&B,int&C){
	//variables de la funcion
	int AmountPeople;
	
	//se pide la informacion del pedido
	cout<<"Nombre del cliente: ";cin>>name;
	
	//cantidad de personas por mesa
	cout<<"Personas por mesa: ";cin>>AmountPeople;
	system("cls");
	
	FoodAmountPayment(PaymentType,amount,A,B,C); //se llama a la funcion donde se eligen los platos de comida, el monto y tipo de pago

}

//funcion donde se ingresa la comida, el monto y tipo de pago
void FoodAmountPayment(char& PaymentType, float& amount, int&A,int&B, int&C){
	//varianles de la funcion
	int k = 0;
	
	//se llaman a las funciones donde se selecciona la comida y debidas
	PrincipalFood(A);
	
	FoodTickets(B);
	
	Drinks(C);
	system("cls");
	
	//se ingresa el monto de la orden
	cout<<"Monto: ";cin>>amount;
	system("cls");
	
	//un ciclo para el pequeño menu de seleccionar el tipo de pago
	while(k==0){
		
		//menu para seleccionar el tipo de pago que hara el cliente
		cout<<"Tipo de pago: \n\n1-Efectivo\n2-Tarjeta de Credito\n"<<endl;
		cout<<"Opcion: ";cin>>PaymentType;
		
		if(PaymentType == '1' || PaymentType == '2'){
			break;
		}	
		system("cls");
	}
	system("cls");
	
}

//FUNCIONES DE LOS MENUS DE COMIDA

//funcion de platos principales
int PrincipalFood(int& A){
	//variables declaradas
	int k = 0;
	char option;
	
	//while donde se muestra el menu de platos principales
	while(k==0){
		
		//MENU DE PLATOS PRINCIPALES			
		cout<<"PLATO PRINCIPAL:\n"<<endl;
		cout<<"1-Pizza\n2-Ensalada\n3-Pasta\n"<<endl;
		cout<<"Opcion: ";cin>>option;
		
		if(option == '1' || option == '2' || option == '3'){ //si la opcion se encuentra en el menu entra al if
			
			if(option == '1'){ //si la opcion fue 1 la funcion retorna 0
				A = 0;
				k = 1; //para salirse del ciclo se modifica el valor de k
			}
			else if(option == '2'){ //si fue 2 retorna 1
				A = 1;
				k = 1;
			}
			else{
				A = 2; //si fue 3 retorna 2
				k = 1;
			}
			
		}
		system("cls");	
	}
	return A;		
}

//funcion de menu de entradas
int FoodTickets(int& B){
	//variables de la funcion
	int k = 0;
	char option;
	
	while(k==0){
				
		//MENU DE ENTRADAS
		cout<<"ENTRADAS:\n"<<endl;
		cout<<"1-Palitos de Pizza\n2-Pan con ajo\n"<<endl;
		cout<<"Opcion: ";cin>>option;
		
		if(option == '1' || option == '2'){ //si la opcion esta en el menu entra al if
			
			if(option == '1'){ //si la opcion fue 1 la funcion retorna 3
				B = 3;
				k = 1; //para salirse del ciclo se modifica el valor de k
			}
			else{
				B = 4; //si fue 2 retorna el 4
				k = 1; 
			}
			
		}
		system("cls");		
	}
	return B;
}

//funcion de menu de bebidas
int Drinks(int& C){
	//variables de la funcion
	int k = 0;
	char option;
	
	while(k==0){
		
		//MENU DE BEBIDAS
		cout<<"BEBIDAS:\n"<<endl;
		cout<<"1-Gaseosa\n2-Te\n"<<endl;
		cout<<"Opcion: ";cin>>option;
		
		if(option == '1' || option == '2'){ //si es una de las opciones existentes entra al if
			
			if(option == '1'){ //si fue 1 se retornara el numero 5
				C = 5;
				k = 1; //para salirse del ciclo se modifica el valor de k
			}
			else{    //si opcion fue 2 se returnara el 6
				C = 6;
				k = 1;
			}
			
		}			
		system("cls");
	}
	return C;
}

//FUNCIONES DE LOS ARCHIVOS DONDE SE GUARDAN LOS PEDIDOS

//funcion de archivo pedidos a domicilio

void HomeOrderFile(char name[10], char& PaymentType, float& amount, string address, string phone, int&A, int&B, int&C){
	
	//arreglo de strings donde esta las opciones de comidas
	string COMIDAS[7] = {"Pizza", "Ensalada", "Pasta", "Palitos de Pizza", "Pan con ajo", "Gaseosa", "Te"};
	string fecha;
	
	fecha = DateFunction(); //se llama la funcion que genera la fecha
 	
	
	//se crea el archivo para guardar las ordenes a domicilio
	ofstream OrderFile("HomeOrder.txt",ios_base::app);
	
	if (OrderFile.is_open()){
		
		//se escribe todo lo que guardara el archivo
		OrderFile<<"Fecha en que se realizo la orden: "<<fecha<<endl;
		OrderFile<<endl;
		
		//nombre de quien hizo el pedido
		OrderFile<<"Cliente: "<<name<<endl;
		
		//direccion de la orden
		OrderFile<<"Direccion: "<<address<<endl;
		
		//telefono del cliente
		OrderFile<<"Telefono: "<<phone<<endl;
		OrderFile<<"\n"<<endl;
		
		//platos y bebidas ordenadas
		OrderFile<<"Orden: "<<endl;
		OrderFile<<"Plato principal: "<<COMIDAS[A]<<endl;
		OrderFile<<"Entrada: "<<COMIDAS[B]<<endl;
		OrderFile<<"Bebida: "<<COMIDAS[C]<<endl;
		OrderFile<<"\n"<<endl;
		
		//monto de la orden
		OrderFile<<"Monto: "<<amount<<endl;
		
		//tipo de pago de la orden
		if(PaymentType == '1'){
			OrderFile<<"Tipo de pago: Efectivo"<<endl;
		}
		else{
			OrderFile<<"Tipo de pago: Tarjeta de Cretido"<<endl;
		}	
		
		OrderFile<<endl;
		OrderFile.close(); //se cierra el archivo
	}
	else{
		cout<<"NO HA LLEGADO NINGUNA ORDEN!"<<endl;
	}
}

//funcion de archivo encargos a restaurante

void OrderFileToRestaurant(char name[10], char& PaymentType, float& amount, int& AmountPeople, int&A, int&B, int&C){
	
	//arreglo de strings donde esta las opciones de comidas
	string COMIDAS[7] = {"Pizza", "Ensalada", "Pasta", "Palitos de Pizza", "Pan con ajo", "Gaseosa", "Te"};
	string fecha;
	
	fecha = DateFunction(); //se llama la funcion que genera la fecha
 	
	
	//se crea el archivo para guardar las ordenes a restaurante
	ofstream OrderFileR("OrderToRestaurant.txt",ios_base::app);
	
	if(OrderFileR.is_open()){
		
		//se escribe todo lo que guardara el archivo
		OrderFileR<<"Fecha en que se realizo la orden: "<<fecha<<endl;
		OrderFileR<<endl;
		
		//nombre de quien hizo el pedido
		OrderFileR<<"Cliente: "<<name<<endl;
		
		//numeros de personas por mesa
		OrderFileR<<"Personas por mesa: "<<AmountPeople<<endl;
		OrderFileR<<"\n"<<endl;
		
		//platos y bebidas ordenadas
		OrderFileR<<"Orden: "<<endl;
		OrderFileR<<"Plato principal: "<<COMIDAS[A]<<endl;
		OrderFileR<<"Entrada: "<<COMIDAS[B]<<endl;
		OrderFileR<<"Bebida: "<<COMIDAS[C]<<endl;
		OrderFileR<<"\n"<<endl;
		
		//monto de la orden
		OrderFileR<<"Monto: "<<amount<<endl;
		
		//tipo de pago de la orden
		if(PaymentType == '1'){
			OrderFileR<<"Tipo de pago: Efectivo"<<endl;
		}
		else{
			OrderFileR<<"Tipo de pago: Tarjeta de Cretido"<<endl;
		}	
		
		OrderFileR<<endl;
		OrderFileR.close(); //se cierra el archivo
		
	}
	else{
		cout<<"NO HA LLEGADO NINGUN ENCARGO!"<<endl;
	}
	
}

//FUNCIONES QUE LEEN LOS ARCHIVOS CREADOS DE PEDIDOS A DOMICILIO Y A RESTAURANTE

//funcion que lee archivo de pedidos a domicilio
void ReadHomeOrders(){
	
	//se lee el archivo de ordenes a domicilio
	string line;
	ifstream miTXT ("HomeOrder.txt"); 
	
	if (miTXT.is_open()){	
	while (getline (miTXT,line)){	
		cout << line << '\n';
	}
	
	system("pause");
	system("cls");
	
	if(miTXT.eof()){	
		cout<<"Se ha terminado de leer. Fin del archivo";
		system("cls");
	}
		miTXT.close();
	}
	else{
		cout << "LOS PEDIDOS A DOMICILIO RECIBIDOS SE GUARDARAN AQUI!\n"<<endl;
		system("pause");
	} 
	
}

//OTRAS FUNCIONES
//funcion que genera la fecha actual
string DateFunction(){
	
	//se genera la fecha actual
	time_t   t,x;
	char *fecha;
	x = time (&t);
	fecha = ctime (&x); 
	
	return fecha;
}
