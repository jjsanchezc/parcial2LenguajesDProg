/*
 Respuesta del parcial 2 de lenguajes de programación 
 Hecho por: Juan José Sánchez Cortés
 En este archivo se encuentra adjunto el código para realizar los problemas propuestos en donde se encuentra el parcial
*/
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class respuestaParcialDos
{
public:
    //punto 5
    int menu1();
    void menu(int opcion); //menu para el usuario

protected:
    //punto 1
    void entrada(string rocio); //se usa cuando se quiera poner el valor en los parametros
    void entrada();             //definir si va a ser por medio de un teclado, leer archivo (sin parametros)
    void lecturaArchivo();      //lee el archivo .txt
    //punto 2
    void crearToken(); //metodo para crear vector
    //punto 3
    bool validar();          //validar si se puede hacer la ecuacion
    bool dobles();           //busca si hay dos variables seguidas para poder hacer la ecuacion
    bool defVar(string c);   //define que es una variable(en string)
    bool defVarChar(char c); //define que es una variable (en char)
    //punto 4
    void calcular(); //hace el calculo de la ecuacion
    //extras
    void mostrarElementos(); //muestra los elementos en pantalla
    void reiniciarTodo();    //reinicia todos los metodos y atributos a como empezaron para que se puedan realizar ecuaciones ilimitadas
    ~respuestaParcialDos(){};

private:
    string expresion;      //esta sera en donde se guarde la string creada de la cual saldra el vector
    vector<string> tokens; //aca se almacenara la expresion en forma de vector
    //los contadores ayudan a la verificacion de la ecuacion
    int contadorOperadores;
    int contadorVariables;
    //----------
    string c;
    char cha;
    long resultado; //resultado final de la ecuacion
};

void respuestaParcialDos::entrada(string albeiro) //ya que para que el ingreso de parametros =null(que se podia poner o evitar) no funciono,toco crear 2 metodos para que leyeran la entrada, esta es la entrada por parametros
{
    this->expresion = albeiro;
    crearToken();
    if (validar() == true)
    {
        calcular();
        reiniciarTodo();
    }
    else
        reiniciarTodo();
}
void respuestaParcialDos::entrada() //ha diferencia del otro metodo, esta funciona para que el usuario pueda leer un archivo .txt o que simplemete ingrese la ecuacion
{
    int seleccionLector;
    cout << "Hola, para definir la expresion que haras \nEscribe 1 seguido de <enter> si lo que quieres es escribir la ecuacion. \nEscribe 2 seguido de <enter> si deseas leer un archivo .txt " << endl;
    cin >> seleccionLector;
    if (seleccionLector == 1)
    {
        cout << "Escribe la ecuación que quieras calcular seguido de <enter>\n    NOTA:Tines que poner un espacio luego de cada letra, ej:+ + 2 3 4" << endl;
        cin.ignore();
        getline(cin, expresion);
        crearToken();
        if (validar() == true)
        {
            calcular();
            reiniciarTodo();
        }
        else
            reiniciarTodo();
        return;
    }
    else if (seleccionLector == 2)
    {
        lecturaArchivo();
    }
    else
    {
        cout << "Lo siento, el caracter usado no es valido, por favor escriba un numero valido";
    }
}
void respuestaParcialDos::crearToken()
{
    stringstream cadena_elementos(expresion);
    char separador = ' ';
    string elemento;
    while (getline(cadena_elementos, elemento, separador))
    {
        tokens.push_back(elemento);
        if (elemento == "+" || elemento == "-" || elemento == "*" || elemento == "/") //define si es una variable o si es un operador para asi poder validar la ecuacion
        {
            contadorOperadores++;
        }
        else if (elemento != "x" || elemento != "-" || elemento != "*" || elemento != "/")
        {
            contadorVariables += 1;
        }
    }
}
bool respuestaParcialDos::validar() //este metodo usa los metodos dobles(), defVarChar() para poder definir si la ecuacion ingresada es valida o no
{
    int seleccionLector2;
    char c = expresion.at(expresion.size() - 1); //si el ultimo valor es un operador, no se puede realizar
                                                 //si hay mas o iguales operadores que variables, no se puede realizar
                                                 //si no hay 2 variables seguidas en ninguna parte, no se puede realizar
                                                 //siempre debe de haber 1 variable mas que los operadores
    if (contadorOperadores >= contadorVariables || contadorOperadores + 1 != contadorVariables || defVarChar(c) == false || dobles() == false)
    {
        cout << "Lo siento, expresion no valida para: \n " << expresion << endl;
        return false;
    }
    else
        cout << "expresion valida para: " << expresion << endl;
    return true;
}
bool respuestaParcialDos::dobles() //este metodo lo que hace es revisar si en todo el vector hay alguna pareja de variables( para poder realizar la operacion)
{
    bool dosVar;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (defVar(tokens[i]) == true)
        {
            if (defVar(tokens[i + 1]) == true)
            {
                return true;
            }
        }
    }
    return false;
}
bool respuestaParcialDos::defVar(string c)
{
    this->c = c;
    if (c == "+")
        return false;
    if (c == "-")
        return false;
    if (c == "*")
        return false;
    if (c == "/")
        return false;
    else
        return true;
}
bool respuestaParcialDos::defVarChar(char c)
{
    this->c = c;
    switch (c)
    {
    case '+':
        return false;
        break;
    case '-':
        return false;
        break;
    case '*':
        return false;
        break;
    case '/':
        return false;
        break;
    default:
        return true;
        break;
    }
}
void respuestaParcialDos::calcular()
{
    for (int z = 1; z < tokens.size() - 1; z++)//calcula el valor de la ecuacion y devuelve la respuesta
    {
        int a, b;
        char j, l;
        stringstream ss(tokens.at(z));
        stringstream sb(tokens.at(z + 1));
        stringstream atex;
        int inicio;
        int fainal;
        string tmp;
        if (defVar(tokens.at(z)) == true) //que la pos actual sea un numero
        {
            if (defVar(tokens[z - 1]) == false) //si el anterior es un operador
            {
                if (defVar(tokens[z + 1]) == true) //si el siguiente es un numero
                {

                    ss >> a;
                    sb >> b;
                    inicio = z - 1;
                    fainal = z + 2;
                    if (tokens.at(z - 1) == "+") //cuando sea suma
                    {
                        resultado = (a + b);
                        atex << resultado;
                        tmp = atex.str();
                        tokens.erase(tokens.begin() + inicio, tokens.begin() + fainal); //lo que hace esto es borrar todos los elementos que tomamos y los borramos para
                        tokens.insert(tokens.begin() + (z - 1), tmp);                   //poder insertar la respuesta que nos dio el resultado de la operacion que acabamos de realizar(esto se hace para cada operador)
                    }
                    else if (tokens.at(z - 1) == "-") //cuando sea resta
                    {
                        resultado = (a - b);
                        atex << resultado;
                        tmp = atex.str();
                        tokens.erase(tokens.begin() + inicio, tokens.begin() + fainal);
                        tokens.insert(tokens.begin() + (z - 1), tmp);
                    }
                    else if (tokens.at(z - 1) == "*") //cuando sea multiplicacion
                    {
                        resultado = (a * b);
                        atex << resultado;
                        tmp = atex.str();
                        tokens.erase(tokens.begin() + inicio, tokens.begin() + fainal);
                        tokens.insert(tokens.begin() + (z - 1), tmp);
                    }
                    else if (tokens.at(z - 1) == "/") //cuando sea division
                    {
                        resultado = (a / b);
                        atex << resultado;
                        tmp = atex.str();
                        tokens.erase(tokens.begin() + inicio, tokens.begin() + fainal);
                        tokens.insert(tokens.begin() + (z - 1), tmp);
                    }
                    z = 0;
                }
            }
        }
    }
    cout << "el resultado es: " << resultado << endl;
}

int respuestaParcialDos::menu1()//aca se ingresa la opcion que el usuario desea realizar
{
    cout << "Hola, bienvenido, este progrma funciona para poder calcular la notacion polaca de alguna ecuacion,\nen el siguiente menu apareceran las opciones que usted puede escoger para poder calcular." << endl;
    cout << "Presione 0 seguido de <enter> para salir del progrma. \nPresione 1 seguido de <enter> para ingresar alguna notacion polaca." << endl;
    cout<<"             NOTA(no tan importante):sentimos que sea dificil de leer, solo que el programa no captura las tildes, por lo tanto no se usan en este programa."<<endl;
    int opcion;
    cin >> opcion;
    return opcion;
}
void respuestaParcialDos::menu(int opcion)//y aca es la interfaz donde se realiza cada opcion
{
    while (opcion > 0)
    {
        cout << "" << endl;
        switch (opcion)
        {
        case 0:
            cout << "gracias por usar el programa, hasta la proxima :)" << endl;
            exit;
            break;
        case 1:
            entrada();
            break;
        default:
            cout << "Lo siento, el caracter usado no es valido, por favor escriba un numero valido";
            break;
        }
        cout << "" << endl;
        cout << "" << endl;
        cout << "Presione 0 seguido de <enter> para salir del progrma. \nPresione 1 seguido de <enter> para ingresar alguna notacion polaca." << endl;
        cin >> opcion;
    }
}
void respuestaParcialDos::mostrarElementos()//muestra cada elemento del vector
{
    for (int i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i];
    }
    cout << "  aca acaban los elementos" << endl;
}
void respuestaParcialDos::lecturaArchivo()
{
    ifstream archivo;
    string arch;
    cout << "por favor ingrese el nombre del archivo, junto al texto '.txt' seguido de <enter>. \n    NOTA:Recuerde que el archivo .txt debe de estar dentro de la misma carpeta para que el progrma pueda leerlo" << endl;
    cin >> arch;
    archivo.open(arch, ios::in); //abrimos archivo en modo lectura
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    while (!archivo.eof())//cuando se lea una linea nueva, el programa automaticamente las leera, validara y calculara su resultado
    { //mientras no sea el final de archivo
        getline(archivo, expresion);
        crearToken();
        if (validar() == true)
        {
            calcular();
            reiniciarTodo();
        }
        else
            reiniciarTodo();
    }
    archivo.close(); //se cierra el progrma
}
void respuestaParcialDos::reiniciarTodo()
{
    expresion = "";
    contadorOperadores = 0;
    contadorVariables = 0;
    c = "";
    cha = 'c';
    resultado = 0;
    tokens.clear();
}
int main()
{
    respuestaParcialDos *p = new respuestaParcialDos();
    p->menu(p->menu1());
    return 0;
}
