#include <iostream>
#include <vector> // Necesario para std::vector en la función de recomendaciones
#include <string> // Necesario para std::string

// Asumiendo que portafolio.h está en el mismo directorio o en el include path
#include "portafolio.h"
// Asumiendo que grafo.h está en el mismo directorio o en el include path
#include "grafo.h"

using namespace std;

int main() {
    // Crear y poblar el portafolio
    Portafolio usuario("Luis");
    usuario.agregarActivo("MSFT"); // Agregado primero para ver el efecto de ordenar
    usuario.agregarActivo("AAPL");
    usuario.agregarActivo("GOOG");

    cout << "=== Portafolio Inicial ===\n";
    usuario.mostrar();
    cout << "---------------------------------\n";

    // Demostrar ordenamiento de activos
    cout << "\n=== Ordenando Activos ===\n";
    usuario.ordenarActivos();
    usuario.mostrar();
    cout << "---------------------------------\n";

    // Demostrar eliminación de un activo existente
    cout << "\n=== Eliminando Activo 'MSFT' ===\n";
    if (usuario.eliminarActivo("MSFT")) {
        cout << "Portafolio después de eliminar 'MSFT':\n";
    } else {
        cout << "'MSFT' no se encontró para eliminar.\n"; // No debería pasar aquí si se agregó
    }
    usuario.mostrar();
    cout << "---------------------------------\n";

    // Demostrar intento de eliminación de un activo no existente
    cout << "\n=== Intentando Eliminar Activo 'TSLA' (no existente en portafolio) ===\n";
    if (usuario.eliminarActivo("TSLA")) {
        cout << "Portafolio después de eliminar 'TSLA':\n"; // No debería pasar aquí
    } else {
        // El mensaje de "no encontrado" ya se imprime desde el método eliminarActivo
    }
    usuario.mostrar();
    cout << "---------------------------------\n";

    // Configuración del grafo de relaciones (como en tu original)
    Grafo grafo;
    // Relaciones para activos que podrían o no estar en el portafolio actual
    grafo.agregarRelacion("AAPL", "NVDA");      // Si tienes AAPL, podrías interesarte en NVDA
    grafo.agregarRelacion("AAPL", "ADBE");
    grafo.agregarRelacion("GOOG", "AMZN");      // Si tienes GOOG, podrías interesarte en AMZN
    grafo.agregarRelacion("MSFT", "MSFT_CLOUD_PARTNER"); // Si tuvieras MSFT...
    grafo.agregarRelacion("AMZN", "NFLX");
    grafo.agregarRelacion("NVDA", "TSLA");

    cout << "\n=== Obteniendo Recomendaciones de Inversión ===\n";
    cout << "Portafolio actual para recomendaciones:\n";
    usuario.mostrar(); // Muestra el estado actual del portafolio (AAPL, GOOG)

    // Obtener recomendaciones basadas en el portafolio actual
    // (después de las eliminaciones y ordenamientos)
    vector<string> recomendaciones = grafo.recomendacionesDesdePortafolio(usuario.obtenerActivos());

    cout << "\nRecomendaciones de inversión:\n";
    if (recomendaciones.empty()) {
        cout << "(No hay nuevas recomendaciones basadas en el portafolio actual o todas las relacionadas ya están en el portafolio)\n";
    } else {
        for (const auto& rec : recomendaciones) {
            // Opcionalmente, verificar si la recomendación ya está en el portafolio
            // if (!usuario.tieneActivo(rec)) {
            cout << "- " << rec << '\n';
            // }
        }
    }
    cout << "---------------------------------\n";

    return 0;
}