# 🚀 Bitácora del Proyecto: MonopolyHasbro

## 📋 Información General

- **Nombre del Proyecto:** MonopolyHasbro
- **Equipo:**  Alfonso Vega & Carlos Sánchez
- **Fecha de Inicio:** 2025-10-28
- **Fecha Estimada de Finalización:** 2025-12-10
- **Objetivo Principal:**  
  Implementar un simulador del juego Monopoly de Hasbro utilizando TADs personalizados en C++, siguiendo estrictamente las reglas del juego y empleando principios de diseño modular, estructuras de datos complejas y control de versiones en GitHub.

---

## 🗓️ Registro Diario

---

### 🔵 Día 1 — 2025-10-28

#### 🎯 Actividades Realizadas
- Revisión del documento de requisitos entregado por el profesor. (1.5h)
- Descarga y estudio de las reglas oficiales del Monopoly de Hasbro. (2h)
- Identificación preliminar de posibles TADs del sistema. (1h)

#### 🚧 Problemas Encontrados
- Ambigüedad en el documento inicial del profesor respecto a la estructura del tablero.  
  **Estado:** Resuelto  
  **Solución:** Analizar las reglas oficiales y extraer estructura real usada en el juego.

#### ✅ Decisiones Clave
- Basar todo el diseño del sistema en las reglas oficiales de Hasbro.  
- Trabajar con arquitectura modular por TAD.

#### ➡️ Próximos Pasos
- Definir atributos de cada TAD.
- Crear el primer borrador de la estructura del repositorio.

---

### 🔵 Día 2 — 2025-10-29

#### 🎯 Actividades Realizadas
- Diseño conceptual de los TADs base: Jugador, Propiedad, Banco, Casilla, Tarjeta. (3h)
- Revisión cruzada entre Alejandro y Alfonso para validar responsabilidades de cada módulo. (1h)

#### 🚧 Problemas Encontrados
- Se plantearon TADs innecesarios que complicaban el futuro del proyecto.  
  **Estado:** Resuelto  
  **Solución:** Alfonso revisó y filtró los TADs esenciales.

#### ✅ Decisiones Clave
- Limitar TADs únicamente a aquellos con responsabilidad real dentro del juego.
- Evitar mezclar lógica del tablero con lógica del banco.

#### ➡️ Próximos Pasos
- Crear repositorio en GitHub e inicializar carpetas.

---

### 🔵 Día 3 — 2025-11-02

#### 🎯 Actividades Realizadas
- Creación del repositorio GitHub. (0.5h)
- Configuración de carpetas `/include`, `/src`, `/docs`, `/assets`, `/data`. (1h)
- Inicio de la bitácora en formato Markdown. (1h)

#### 🚧 Problemas Encontrados
- Dudas iniciales sobre cómo estructurar correctamente la bitácora.  
  **Estado:** Resuelto  
  **Solución:** Se investigaron plantillas e integró una plantilla profesional como esta.

#### ✅ Decisiones Clave
- Alejandro liderará documentación y GitHub.
- Alfonso liderará implementación de TADs.

#### ➡️ Próximos Pasos
- Implementar TAD Jugador y Banco.

---

### 🔵 Día 4 — 2025-11-05

#### 🎯 Actividades Realizadas
- Implementación inicial de Jugador.cpp y Jugador.h. (3h)
- Implementación de Banco.cpp y Banco.h según lógica de Hasbro (2h)

#### 🚧 Problemas Encontrados
- Errores en sincronización entre ramas *main* y *master*.  
  **Impacto:** Medio  
  **Estado:** Resuelto parcialmente  
  **Solución:** Mover todo trabajo real a la rama **main**.

#### ✅ Decisiones Clave
- Se abandona la rama *master*.
- Oficializar *main* como la rama de desarrollo activo.

#### ➡️ Próximos Pasos
- Implementar TAD Propiedad.
- Cargar los datos desde archivos `.txt`.

---

### 🔵 Día 5 — 2025-11-10

#### 🎯 Actividades Realizadas
- Creación de archivos `.txt` que representan propiedades y tarjetas oficiales del Monopoly. (2h)
- Implementación de TAD Propiedad con su lógica de hi
