#include "estado.hpp"

std::string_view toString(Estado estado) {
    switch (estado) {
        case Estado::Active: return "Conectado";
        case Estado::Away:   return "Ausente";
        case Estado::Busy:   return "Ocupado";
    }
    return "";
}
