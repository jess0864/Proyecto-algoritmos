# 📈 Simulador de Bolsa e Inteligencia de Inversión para Acciones

Este proyecto implementa un sistema de simulación bursátil en C++ que permite a los usuarios explorar, analizar y gestionar portafolios de inversión sobre acciones de empresas colombianas (o simuladas), considerando eventos externos como noticias económicas y sectoriales. El sistema está completamente documentado con **Doxygen** y estructurado en módulos independientes.

---

## 🎯 Objetivo

- Consultar y analizar empresas por sector, precio o nombre.
- Simular el impacto de noticias sobre el precio de acciones.
- Comprar, vender y gestionar un portafolio de inversión personal.
- Recibir recomendaciones de compra basadas en análisis técnico y noticias.
- Aplicar estructuras de datos y algoritmos avanzados.

---

## 🧱 Componentes del Sistema

| Componente               | Estructura           | Archivo            | Funcionalidad principal                                        |
|--------------------------|----------------------|---------------------|----------------------------------------------------------------|
| Empresas                 | Árbol ABB            | `empresa.h`         | Almacena empresas ordenadas por ticker.                       |
| Precios históricos       | Multilista           | `empresa.h`         | Guarda historial de precios para cada empresa.                |
| Noticias financieras     | Cola de prioridad    | `noticia.h`         | Ordena e inserta noticias con impacto en sectores.            |
| Portafolio del usuario   | Pila + Vector        | `portafolio.h`      | Guarda activos del usuario y permite ordenarlos/eliminarlos. |
| Lógica del sistema       | Menú principal       | `codigo.cpp`        | Integra todos los módulos y ofrece menús interactivos.        |

---

## 🔍 Algoritmos utilizados

- **Búsqueda**:
  - Búsqueda binaria en ABB de empresas.
  - Búsqueda de empresas por rango de precio y sector.

- **Ordenamiento**:
  - `MergeSort` para ordenar empresas por precio.
  - Ordenamiento alfabético de activos en pila.
  - `MergeSort` de noticias por fecha.

- **Análisis**:
  - Promedio móvil de precios.
  - Recomendaciones de compra usando análisis de tendencias y noticias.
  - Cálculo de volatilidad (desviación estándar) de precios.

---

## 🛠️ Funcionalidades del Menú

- **Consulta de empresas**: buscar por ticker, listar alfabéticamente o por precio.
- **Consulta por sector**: agrupar y calcular promedios sectoriales.
- **Simulación y noticias**:
  - Insertar o generar noticias aleatorias.
  - Ajustar precios de acciones según impacto.
  - Ver noticias por prioridad o fecha.
  - Detectar crisis por acumulación de noticias negativas.
- **Gestión del portafolio**:
  - Comprar y vender acciones.
  - Ver contenido actual y presupuesto.
  - Recomendaciones inteligentes por sector y tendencia.
  - Deshacer última acción con pila.
  - Ordenar activos del portafolio.
