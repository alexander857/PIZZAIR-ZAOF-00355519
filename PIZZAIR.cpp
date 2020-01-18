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
//funcion de menu principal
char PizzaMenu();

//funciones de pedidos
float FoodAmountPayment(char&,float&,int&,int&,int&); //se selecciona la comida, el tipo de pago y el monto


//otras funciones 
string DateFunction(); //genera la fecha actual
void TotalSales(float&,float&); //calcula el total de ventas

int main(){
	//DECLARACION DE VARIABLES 
	//contrase?a para el menu principal
	char password[]="delete", key[6], PaymentType, name[10], option;  
	int k = 0, A = 0, B = 0, C = 0;
	float amount = 0, p = 0, n = 0; 	
	
	//pedimos la contrase?a para ingresar
	cout<<"SOLO PERSONAL AUTORIZADO!\n"<<endl;
	cout<<"Ingrese la clave: ";cin>>key;
	
	//hay solo 3 intentos para ingresar la contrase?a correcta
	while(k==0){
		
		//se compara si la contrase?a es correcta
		if(strcmp(password,key) == 0){ //compara las dos palabras: password y key 
			
			system("cls"); 
			option = PizzaMenu(); //se llama la funcion del menu principal si la contrase��a es correcta
			system("cls");
			
			//condiciones segun lo que se seleccione en el menu principal
			if(option == '1'){
				
				HomeOrders(name,PaymentType,amount,A,B,C,n); //se llama a la funcion para agregar un pedido a domicilio
				
			}
			else if(option == '2'){
				
				CustomInRestaurant(name,PaymentType,amount,A,B,C,p); //se llama la funcion para agregar encargo a restaurante
				
			}
			else if(option == '3'){
				
				ReadHomeOrders(); //se llama la funcion que lee el archivo de pedidos a domicilio
				
			}
			else if(option == '4'){
				
				ReadOrderRestaurant(); //se llama la funcion que lee el archivo de encargos a restaurante
				
			}
			else if(option == '5'){
				
				TotalSales(p,n); //se llama la funcion que muestra las ventas totales

			}
			else if(option == '6'){
				
				break;  //al seleccionar la opcion salir se cierra el programa
				
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
	cout<<"1-Agregar 1 pedido a domicilio\n2-Agregar 1 encargo en restaurante\n3-Ver pedidos a domicilio\n"
	"4-Ver encargos en restaurante\n5-Ver total de ventas\n6-Salir\n"<<endl;
	
	//se pide una opcion a seleccionar
	cout<<"Opcion: ";cin>>option;
	
	return option;
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

//funcion que lee el archivo de los encargos a restaurante
void ReadOrderRestaurant(){
	
	//se lee el archivo de ordenes a domicilio
	string line;
	
	ifstream miTXT ("OrderToRestaurant.txt");
	
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
		cout << "LOS ENCARGOS A RESTAURANTE RECIBIDOS SE GUARDARAN AQUI!\n"<<endl;
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
	
	return fecha; //se retorna la fecha para las funciones donde se crean los archivos de las ordenes
}

//funcion que suma el monto de ordenes a domicilio con el monto de ordenes a restaurante
void TotalSales(float& p, float& n){
	float Total = 0;
	
	Total = p + n; //el valor que resiven las variables p y n de los montos ingresados en los pedidos, se suman y hacen el total del monto
	
	cout<<"Ventas totales: $"<<Total<<"\n"<<endl; //se muestra en pantalla ventas totales
	system("pause");

}
