#include "demoRegex.h"
#include <iostream>
#include <regex>
#include "types.h"

using namespace std;

void demoRegex()
{
    cout << endl << "======================================" << endl;
    cout << ">>>>>>>>>>Demo Regex: " << endl;

    //-----------------------------------------------------------------
    // 1. regex_match
    //-----------------------------------------------------------------
    string correo = "jorge.garcia@outlook.com";
    regex patronCorreo(R"(\w+(\.\w+)?@\w+\.\w+(\.\w+)?)");
    //R es para darle el formato Raw String Literal (\\ se escribe como \)
    // \w caracter alfanumerico o guion bajo, + (uno o mas)
    // \w+ acepta: usuario123, abc_def, jorge
    
    // (\.\w+)?
    // "." acepta cualquier caracter pero como se desea un punto literal se debe
    // usar "\."
    // ? indica que es una parte opcional

    //@ es obligatorio para la estructura

    bool esCorreo = regex_match(correo, patronCorreo);
    cout << "Correo: " << correo << endl;
    cout << "regex_match(): " << (esCorreo ? "Correo valido" : "Correo invalido") << endl << endl;

    //-----------------------------------------------------------------
    // 2. regex_search
    //-----------------------------------------------------------------
    string texto = "El estudiante obtuvo 18 de nota final.";
    regex patronNumero(R"(\d+)");
    // \d digito decimal del 0 al 9.
    // + una o mas veces
    smatch resultado;

    // search solo encuentra la primera coincidencia con el texto
    if (regex_search(texto, resultado, patronNumero))
        cout << "Primer numero encontrado: " << resultado.str()  << endl << endl;
    

    //-----------------------------------------------------------------
    // 3. Buscar todas las coincidencias
    //-----------------------------------------------------------------
    string lista = "10 25 38 44 91";
    regex numeros(R"(\d+)");

    cout << "Numeros encontrados:" << endl;

    TI contador = 1;

    for (sregex_iterator it(lista.begin(), lista.end(), numeros); it != sregex_iterator(); ++it)
    {
        cout << contador << ": " << it->str() << endl;
        ++contador;
    }

    cout << endl;

    //-----------------------------------------------------------------
    // 4. regex_replace
    //-----------------------------------------------------------------
    string frase = "Hoy es 13/07/2026.";
    regex fecha(R"(\d{2}/\d{2}/\d{4})");
    string nuevaFrase = regex_replace(frase, fecha, "[FECHA]");

    cout << "Original : " << frase << endl;
    cout << "Modificada: " << nuevaFrase << endl;

    cout << endl;
    cout << "=========== FIN DEMO ===========" << endl;
}