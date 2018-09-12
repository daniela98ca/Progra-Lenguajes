#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*Para cargar archivos .txt*/
/*
    Modos: 
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

Medicos* agregarMedico2(Medicos* nuevo,Medicos* inicio){
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
 Funcion para cargar los archivos de texto que contienen los datos del programa
 No contiene entradas
 Tiene como salida un puntero a un fichero
 */
FILE* cargar(){
    FILE* fichero_medicos;
    FILE* fichero_pacientes;
    FILE* fichero_citas;
    fichero_medicos=fopen("medicos.txt","a");
    fichero_pacientes=fopen("pacientes.txt","a");
    fichero_citas=fopen("citas.txt","a");
    if(fichero_medicos==NULL && fichero_pacientes==NULL && fichero_citas==NULL){
        printf("No se pudo cargar el archivo");
    }
    else{
    printf("Se cargo correctamente\n");
    }
    return fichero_medicos;
    return fichero_pacientes;
    return fichero_citas;
}

void guardarMedico(FILE* fichero_medico,char* nombre, int codigo,char* apellido,char* especialidad,char* turno)
{
    if(fichero_medico==NULL){
        printf("No se ha podido cargar el fichero");
    }
    else{
        fprintf(fichero_medico,"%d,",codigo);
        fprintf(fichero_medico,"%s,",nombre);
        fprintf(fichero_medico,"%s,",apellido);
        fprintf(fichero_medico,"%s,",especialidad);
        fprintf(fichero_medico,"%s,-",turno);
    }
}

/*Medicos* leerarchivo(FILE* fichero){
    fichero=fopen("exampleA.txt","rt");
        char c;
        c=fgetc(fichero);
        char informacion[25];
        char infovacia[25];
        
        int contadoratributos=1;
        int contadormedicos=0;
        int caracteres=0;
        
        Medicos* inicio=NULL;
        Medicos* nuevo=(Medicos*)malloc(sizeof(Medicos));
   
    if(fichero==NULL){
        printf("No se pudo cargar el archivo");
    }
    else if(feof(fichero)!=0){
        printf("El archivo se encuentra vacio");
    }
    else{
        while(feof(fichero)==0){
            
            if(c==','){
                contadoratributos++;
                c=fgetc(fichero);
            }
            else if(c=='-'){
                contadormedicos++;
                contadoratributos=0;
                inicio=agregarMedico2(nuevo,inicio); 
            }
            else{
                informacion[caracteres]=c;
                caracteres++;
                if(fgetc(fichero)==','){
                    if(contadoratributos==0){
                        nuevo->codigo=c-'0';
                    }
                    else if(contadoratributos==1){
                        nuevo->nombre=informacion;
                    }
                    else if(contadoratributos==2){
                        nuevo->apellido1=informacion;
                                               
                    }
                    else if(contadoratributos==3){
                        nuevo->especialidad=informacion;
                        
                    }
                    else if(contadoratributos==4){
                        nuevo->turno=informacion;
                    }
                    contadoratributos++;
                    informacion=infovacia; 
                    caracteres=0;
              
                    }
            }
            c=fgetc(fichero);
            printf("%c",c);
        }
    }
        fclose(fichero);
        imprimirMedicos(inicio);
        return inicio;
}*/

/*
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

/*
Recibe puntero y la identificación del cliente
Sirve para buscar un paciente en la lista 
retorna true o false
 */
bool existePaciente(int identificacion, Pacientes* ptr){
    while(ptr!=NULL){
        if(ptr->identificacion==identificacion) 
        {
            return true;
        }
        else{
            ptr=ptr->siguiente;
        }
    }
    return false;
}

Pacientes* agregarPacientes(int identificacion, char* nombre, char* apellido, int edad, int numero, Pacientes* ini){
    Pacientes* nuevo=(Pacientes*)malloc(sizeof(Pacientes));
    nuevo->identificacion=identificacion;
    strcpy(nuevo->nombre,nombre);
    strcpy(nuevo->apellido1,apellido);
    nuevo->edad=edad; 
    //nuevo->numero=numero;
        if(ini== NULL)
        {
            ini=nuevo;
            nuevo->siguiente=NULL;
        }
        else{
            nuevo->siguiente=ini;
            ini=nuevo;
        }
        printf("El paciente se agregó correctamente\n");
        return ini;       
    }
Pacientes* agregarPacientes2(Pacientes* nuevo,Pacientes* inicio){
    nuevo->siguiente=inicio;
}

void guardarPacientes(FILE* fichero_pacientes,int identificacion, char* nombre,char* apellido, int edad)
{
    if(fichero_pacientes==NULL){
        printf("No se ha podido cargar el fichero");
    }
    else{
        fprintf(fichero_pacientes,"%d,",identificacion);
        fprintf(fichero_pacientes,"%s,",nombre);
        fprintf(fichero_pacientes,"%s,",apellido);
        fprintf(fichero_pacientes,"%d",edad);
        //fprintf(fichero_pacientes,"%d,-",numero);
    }
}

/*
 Recibe un puntero a la lista de pacientes
 Sirve para imprimir todos los pacientes de la lista
 */
void imprimirPacientes(Pacientes* ptr){
    while(ptr!=NULL){
        printf("Identificacion: %d  Nombre: %s Apellido: %s Edad: %d\n",ptr->identificacion,ptr->nombre,ptr->apellido1, ptr->edad);
        ptr=ptr->siguiente;
    }
}

int main(int argc, char** argv) {
    int respuesta;
    FILE* fichero_medicos;
    FILE* fichero_pacientes;
    FILE* fichero_citas;

    //Atributos de medicos
    int codigoMedico;
    char nombreMedico[15];
    char apellidoMedico[15];
    char especialidad[25];
    char turno[15];
    Medicos* inicio=NULL; 
    
    //Atributos de las citas
    int cod_medico;
    int id_cliente;
    int hora;
    //int fecha;
    Citas* ini=NULL; 
    
    //Atributos de los pacientes
    int identificacion;
    char nombrePaciente[15];
    char apellidoPaciente[15];
    int edad;
    NumTelefono numero;
    //Pacientes* inicio=NULL; 
    
    while(respuesta!=5){ 
        printf("--------------Menu de opciones------------ \n Seleccione la opción que desea :\n 1.Cargar datos \n 2.Registrar nuevo medico \n 3.Programar cita \n 4.Estadisticas \n 5.Salir\n");
        scanf("%d",&respuesta);
        if(respuesta==1){ 
            printf("-----------Cargando archivos-----------\n");
            fichero_medicos=cargar();
            fichero_citas=cargar();
            fichero_pacientes=cargar();
        }
        else if(respuesta==2){
            printf("-----------Agregando Medicos-----------\n");
            printf("Escriba el codigo del nuevo medico: ");
            scanf("%d",&codigoMedico);
            
            if(existeMedico(codigoMedico,inicio)){
                printf("El codigo ya fue asignado, no se pudo agregar el medico\n");
                exit(1);
       
            }
            else{
                printf("Escriba el nombre del medico:  ");
                scanf("%s",nombreMedico);
                printf("Escriba el primer apellido del medico: ");
                scanf("%s",apellidoMedico);
                printf("Escriba la especialidad del medico: "); 
                scanf("%s",especialidad);
                printf("Escriba el turno del medico(mañana,tarde,todo el dia): ");
                scanf("%s",turno);
                inicio=agregarMedico(nombreMedico,codigoMedico,apellidoMedico,especialidad,turno,inicio); 
                //fprintf(fichero,"%c CODIGO:%d-NOMBRE:%s-APELLIDO:%s-ESPECIALIDAD:%s-TURNO:%s ",'\n',codigoMedico,nombreMedico,apellidoMedico,especialidad,turno);
//                fprintf(fichero,"%d,%s,%s,%s,%s \n",codigoMedico,nombreMedico,apellidoMedico,especialidad,turno);
                guardarMedico(fichero_medicos,nombreMedico,codigoMedico,apellidoMedico,especialidad,turno);
            }
        }
            
        else if(respuesta==3){
            printf("-----------Programando una cita-----------\n");
            printf("Escriba el codigo del medico: ");
            scanf("%d",&cod_medico);
            printf("Escriba la identificacion del cliente: ");
            scanf("%d",&id_cliente);
            printf("Escriba la hora de la cita: ");
            scanf("%d",&hora);
            //printf("Escriba la fecha de la cita: ");
            //scanf("%d",fecha);
            ini=agregarCitas(cod_medico,id_cliente,hora,ini);
            guardarCita(fichero_citas,cod_medico,id_cliente,hora);
            /*printf("-----------Leer Datos-----------\n");
            fichero_medicos=fopen("medicos.txt","rt");
            if(fichero_medicos==NULL){
            printf("No se pudo cargar el archivo");
            }
            char c;
            
            while (feof(fichero_medicos) == 0){
                c = fgetc(fichero_medicos);
                printf("%c", c);
            } 
            fclose(fichero_medicos);
            return 0;*/
            /*inicio=leerdatos(fichero);
            imprimirMedicos(inicio);
            (fichero);*/
            
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