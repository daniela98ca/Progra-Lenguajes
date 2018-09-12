#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*Para cargar archivos .txt*/
/*Modos: 
 * r: lectura unicamente
 * w:escritura, si no existe se crea, si existe lo reemplaza
 * a: añadir datos al final, si no existe se crea
 * b: binario 
 */

//Creacion de tipo de datos para los numeros telefonicos 
typedef int NumTelefono [8];

//ESTRUCTURAS DEL PROGRAMA
typedef struct Medico{
    int codigo;
    char nombre[25];
    char apellido1[25];
    char especialidad[25];
    char turno[25];
    struct Medico* siguiente;
}Medicos;

typedef struct Paciente{
  int identificacion;
  char nombre[25];
  char apellido1[25];
  int edad;
  NumTelefono numero;
  struct Paciente* siguiente;
}Pacientes;

typedef struct Cita{
    int cod_medico;
    int id_cliente;
    int hora; //(08-19)
    //falta fecha dd-mm-aaaa 
    struct Cita* siguiente;
}Citas; 

//FUNCIONES
/*
 Funciones para cargar los archivos de texto que contienen los datos del programa
 No contiene entradas
 Tiene como salida un puntero a un fichero
 */

//Cargar archivo de Medicos
FILE* cargarMedicos(){
    FILE* fichero;
    fichero=fopen("medicos.txt","a");
    if(fichero==NULL)
    {
        printf("No se pudo cargar el archivo de medicos\n");
    }
    else
    {
        printf("Se cargo correctamente el archivo de medicos\n");
    }
    return fichero;
}

//Cargar archivos de Pacientes
FILE* cargarPacientes(){
    FILE* fichero;
    fichero=fopen("pacientes.txt","a");
    if(fichero==NULL)
    {
        printf("No se pudo cargar el archivo de pacientes\n");
    }
    else
    {
    printf("Se cargo correctamente el archivo de pacientes\n");
    }
    return fichero;
}
//Cargar archivo de Citas  
FILE* cargarCitas(){
    FILE* fichero;
    fichero=fopen("citas.txt","a");
    if(fichero==NULL){
        printf("No se pudo cargar el archivo de citas\n");
    }
    else
    {
    printf("Se cargo correctamente el archivo de citas\n");
    }
    return fichero;
}

int archivoVacio(FILE* fichero){
    char c;
    c=fgetc(fichero);
    if((feof(fichero))!=0){
        return 1;
    }
    else{
        return 0;
    }
}


/*
 Funcion para vaciar un arreglo de caracteres
 */
void vaciararreglo(char temp[]){
    int i;
    for(i=0;i<50;i++){
        temp[i]='\0';
    }
}


/*
Recibe puntero y codigo
Sirve para buscar un medico en la lista 
retorna true o false
 */
bool existeMedico(int codigo, Medicos* ptr){
    while(ptr!=NULL){
        if(ptr->codigo==codigo)
        {
            return true;
        }
        else{
            ptr=ptr->siguiente;
        }
    }
    return false;
}

/*
 Recibe los datos del nuevo medico y un puntero a la lista de medicos
 Sirve para agregar nuevos medicos 
 Retorna el ultimo medico agregado
 */
Medicos* agregarMedico(char* nombre,int codigo,char* apellido,char* especialidad,char* turno ,Medicos* ini){
    Medicos* nuevo=(Medicos*)malloc(sizeof(Medicos));
    strcpy(nuevo->nombre,nombre);
    strcpy(nuevo->apellido1,apellido);
    strcpy(nuevo->especialidad,especialidad);
    strcpy(nuevo->turno,turno);
    nuevo->codigo=codigo;    
        if(ini== NULL)
        {
            ini=nuevo;
            nuevo->siguiente=NULL;
        }
        else{
            nuevo->siguiente=ini;
            ini=nuevo;
        }
        printf("El nuevo médico se agregó correctamente\n");
        return ini;       
    }  

/*
 Funcion para agregar un nuevo médico a la lista 
 */
Medicos* agregarMedicoEstructura(Medicos* nuevo,Medicos* inicio){
    nuevo->siguiente=inicio;
}

/*
 Recibe un puntero a la lista de medicos
 Sirve para imprimir todos los medicos de la lista
 */
void imprimirMedicos(Medicos* ptr){
    while(ptr!=NULL){
        printf("Codigo: %d  Nombre: %s Apellido: %s Especialidad: %s Turno: %s \n",ptr->codigo,ptr->nombre,ptr->apellido1,ptr->especialidad,ptr->turno);
        ptr=ptr->siguiente;
    }
}

/*
 Funcion para guardar los datos de los medicos en el archivo .txt 
 */
int guardarMedico(FILE* fichero,char* nombre, int codigo,char* apellido,char* especialidad,char* turno)
{
    if(fichero==NULL)
    {
        printf("No se ha podido cargar el fichero\n");
        return 0;
    }
    else
    {
        fprintf(fichero,"%d,",codigo);
        fprintf(fichero,"%s,",nombre);
        fprintf(fichero,"%s,",apellido);
        fprintf(fichero,"%s,",especialidad);
        fprintf(fichero,"%s-",turno);
        return 1;
    }
}


/*
 ------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------
 Recibe los datos de la nueva cita y un puntero a la lista de citas
 Sirve para agregar nuevas citas 
 Retorna la ultima cita agregada
 */
Citas* agregarCitas(int cod_medico,int id_cliente,int hora,Citas* ini){
    Citas* nuevo=(Citas*)malloc(sizeof(Citas));
    nuevo->cod_medico=cod_medico;
    nuevo->id_cliente=id_cliente;
    nuevo->hora=hora;
    //nuevo->fecha=fecha;
        if(ini== NULL)
        {
            ini=nuevo;
            nuevo->siguiente=NULL;
        }
        else{
            nuevo->siguiente=ini;
            ini=nuevo;
        }
        printf("La cita se agregó correctamente\n");
        return ini;       
    }

Citas* agregarCitas2(Citas* nuevo,Citas* inicio){
    nuevo->siguiente=inicio;
}

/*
 Funcion para agregar las citas en el archivo de citas
*/
void guardarCita(FILE* fichero_citas,int cod_medico, int id_cliente,int hora)
{
    if(fichero_citas==NULL){
        printf("No se ha podido cargar el fichero");
    }
    else{
        fprintf(fichero_citas,"%d,",cod_medico);
        fprintf(fichero_citas,"%d,",id_cliente);
        fprintf(fichero_citas,"%d,",hora);
        //fprintf(fichero_citas,"%d,-",fecha);
    }
}

/*
 Recibe un puntero a la lista de citas
 Sirve para imprimir todos las citas de la lista
 */
void imprimirCitas(Citas* ptr){
    while(ptr!=NULL){
        printf("Codigo de medico: %d  Identificacion del cliente: %d Hora: %d\n",ptr->cod_medico,ptr->id_cliente,ptr->hora);
        ptr=ptr->siguiente;
    }
}


int ContarCitas(Citas* ptr,int codigoMedico, int hora)
{
    int total=0;
    while(ptr!=NULL){
        if(codigoMedico==ptr->cod_medico){
            
        }
    }
}



/*
 ------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------
 */


int main(int argc, char** argv) {
    int respuesta;
    FILE* ficheroMedicos;
    FILE* ficheroCitas;
    FILE* ficheroPacientes;

    //Atributos de medicos
    int codigoMedico;
    char nombreMedico[15];
    char apellidoMedico[15];
    char especialidad[25];
    char turno[15];
    
    //Inicio para las listas de Medicos, Citas y Pacientes
    Medicos* inicioMedico=NULL; 
    Citas* inicioCitas=NULL;
    Pacientes* inicioPacientes=NULL;
    
    //Atributos de los pacientes
    int identificacion;
    char nombrePaciente[15];
    char apellidoPaciente[15];
    int edad;
    NumTelefono numero;
    
    //Atributos de las citas
    int cod_medico;
    int id_cliente;
    int hora;
    
    
    
    while(respuesta!=5){ 
        printf("--------------Menu de opciones------------ \n Seleccione la opción que desea :\n 1.Cargar datos \n 2.Registrar nuevo medico \n 3.Programar cita \n 4.Estadisticas \n 5.Salir\n");
        scanf("%d",&respuesta);
        if(respuesta==1)
        { 
            printf("-----------Cargando archivos-----------\n");
            ficheroMedicos=cargarMedicos();
            ficheroCitas=cargarPacientes();
            ficheroPacientes=cargarCitas();
            
           /* 
            if((archivoVacio(ficheroMedicos))==1)
            {
                printf("El archivo de medicos no contenia datos");
            }
            else if((archivoVacio(ficheroCitas))==1)
            {
                printf("El archivo de citas no contenia datos");
            }
            else if((archivoVacio(ficheroPacientes))==1)
            {
                printf("El archivo de pacientes no contenia datos");
            }
            * 
            */

        }
        else if(respuesta==2)
        {
            printf("-----------Agregando Medicos-----------\n");
            printf("Escriba el codigo del nuevo medico: ");
            scanf("%d",&codigoMedico);
            
            if(existeMedico(codigoMedico,inicioMedico))
            {
                printf("El codigo ya fue asignado, no se pudo agregar el medico\n");
                exit(1);
            }
            else
            {
                if(ficheroMedicos==NULL)
                {
                 printf("Debe cargar el archivo de Medicos primero");   
                }
                else
                {
                    printf("Escriba el nombre del medico:  ");
                    scanf("%s",nombreMedico);
                    printf("Escriba el primer apellido del medico: ");
                    scanf("%s",apellidoMedico);
                    printf("Escriba la especialidad del medico: "); 
                    scanf("%s",especialidad);
                    printf("Escriba el turno del medico(mañana(M),tarde(T),todo el dia(A): ");
                    scanf("%s",turno);
                    guardarMedico(ficheroMedicos,nombreMedico,codigoMedico,apellidoMedico,especialidad,turno);
                    inicioMedico=agregarMedico(nombreMedico,codigoMedico,apellidoMedico,especialidad,turno,inicioMedico); 
                }
            }
        }
            
        else if(respuesta==3)
        {
            printf("-----------Programando una cita-----------\n");
            printf("Escriba el codigo del medico: ");
            scanf("%d",&cod_medico);
            printf("Escriba la identificacion del cliente: ");
            scanf("%d",&id_cliente);
            printf("Escriba la hora de la cita: ");
            scanf("%d",&hora);
            
            //printf("Escriba la fecha de la cita: ");
            //scanf("%d",fecha);
            /*
            inicioCitas=agregarCitas(cod_medico,id_cliente,hora,inicioCitas);
            guardarCita(ficheroCitas,cod_medico,id_cliente,hora);
            */
            
        }
        else if(respuesta==4){
            printf("-----------Estadisticas-----------\n");
            
        }
        }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
   
    // FILE* fichero;
    //cargar();
 
    //char buffer[100]="Esto es un texto dentro del fichero.\n";
 	
    //fichero=fopen("examplec.txt","a");
    
    //if(fichero==NULL){
      //  printf("El fichero no se pudo cargar");
    //}
   // else{
     //   printf("El fichero se creo correctamente\n");
 
        //fprintf(fichero,"HOLAAA");
        
 	//fprintf(fichero,buffer);
 	
    //}
   //printf("La direccion del fichero es: %p\n",fichero);
    //fclose(fichero);
    return (EXIT_SUCCESS);
}