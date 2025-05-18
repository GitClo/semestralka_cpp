#include <iostream>
#include <memory>
#include <string>
#include <limits>

//#include "include/json.hpp"
//using json = nlohmann::json;

#include "list.h"
#include "plot.h"
#include "citizen.h"

LinkedList<Citizen> citizens;
int next_citizen_id = 1;
int next_plot_id = 1;

void show_menu();
void add_citizen();
void view_citizens();
void find_citizen();
void update_citizen();
void delete_citizen();
void add_plot_to_citizen();
void view_citizen_plots();
void update_plot();
void delete_plot();
std::shared_ptr<Citizen> find_citizen_by_id(int id);
std::shared_ptr<Plot> find_plot_by_id(std::shared_ptr<Citizen>& citizen, int plot_id);

// Pomocna funkcia na vycistenie vstupneho buffera
void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Pomocna funkcia na ziskanie cisla od pouzivatela kvoli menu
int get_int_input(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clear_input_buffer();
            return value;
        } else {
            std::cout << "Neplatny vstup. Prosim zadajte cislo.\n";
            clear_input_buffer();
        }
    }
}

// Pomocna funkcia na ziskanie realneho cisla od pouzivatela
double get_double_input(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            clear_input_buffer();
            return value;
        } else {
            std::cout << "Neplatny vstup. Prosim zadajte kladne cislo.\n";
            clear_input_buffer();
        }
    }
}

// Hlavna funkcia
int main() {
    int choice;

    while (true) {
        show_menu();
        choice = get_int_input("Zadajte volbu: ");

        switch (choice) {
            case 1:
                add_citizen();
                break;
            case 2:
                view_citizens();
                break;
            case 3:
                find_citizen();
                break;
            case 4:
                update_citizen();
                break;
            case 5:
                delete_citizen();
                break;
            case 6:
                add_plot_to_citizen();
                break;
            case 7:
                view_citizen_plots();
                break;
            case 8:
                update_plot();
                break;
            case 9:
                delete_plot();
                break;
            case 0:
                std::cout << "Ukoncujem program...\n";
                return 0;
            default:
                std::cout << "Neplatna volba. Skuste znova.\n";
        }

        std::cout << "\nStlacte Enter pre pokracovanie...";
        std::cin.get();
    }

    return 0;
}

// Zobrazenie menu aplikacie
void show_menu() {
    std::cout << "\n===== SPRAVA OBCANOV A POZEMKOV =====\n";
    std::cout << "1. Pridat obcana\n";
    std::cout << "2. Zobrazit vsetkych obcanov\n";
    std::cout << "3. Vyhladat obcana\n";
    std::cout << "4. Aktualizovat obcana\n";
    std::cout << "5. Vymazat obcana\n";
    std::cout << "6. Pridat pozemok obcanovi\n";
    std::cout << "7. Zobrazit pozemky obcana\n";
    std::cout << "8. Aktualizovat pozemok\n";
    std::cout << "9. Vymazat pozemok\n";
    std::cout << "0. Ukoncit program\n";
    std::cout << "===================================\n";
}

// Pridanie noveho obcana
void add_citizen() {
    std::string first_name, last_name, birth_number, address;

    std::cout << "\n===== PRIDANIE NOVEHO OBCANA =====\n";

    std::cout << "Zadajte meno: ";
    std::getline(std::cin, first_name);

    std::cout << "Zadajte priezvisko: ";
    std::getline(std::cin, last_name);

    std::cout << "Zadajte rodne cislo: ";
    std::getline(std::cin, birth_number);

    std::cout << "Zadajte adresu: ";
    std::getline(std::cin, address);

    auto new_citizen = std::make_shared<Citizen>(next_citizen_id++, first_name, last_name, birth_number, address);
    citizens.push_front(new_citizen);

    std::cout << "Obcan bol uspesne pridany s ID: " << new_citizen->get_id() << "\n";
}

// Zobrazenie vsetkych obcanov
void view_citizens() {
    std::cout << "\n===== ZOZNAM VSETKYCH OBCANOV =====\n";

    if (citizens.is_empty()) {
        std::cout << "Ziadni obcania nie su evidovani.\n";
        return;
    }

    auto current = citizens.get_head();
    while (current) {
        auto citizen = current->get_data();
        std::cout << "ID: " << citizen->get_id()
                  << ", Meno: " << citizen->get_first_name()
                  << ", Priezvisko: " << citizen->get_last_name()
                  << ", Rodne cislo: " << citizen->get_birt_number()
                  << ", Adresa: " << citizen->get_address() << "\n";
        current = current->get_next();
    }
}

// Najdenie obcana pomocou ID
std::shared_ptr<Citizen> find_citizen_by_id(int id) {
    auto current = citizens.get_head();
    while (current) {
        auto citizen = current->get_data();
        if (citizen->get_id() == id) {
            return citizen;
        }
        current = current->get_next();
    }
    return nullptr;
}

// Vyhladanie obcana
void find_citizen() {
    std::cout << "\n===== VYHLADANIE OBCANA =====\n";
    int id = get_int_input("Zadajte ID obcana: ");

    auto citizen = find_citizen_by_id(id);
    if (citizen) {
        std::cout << "Obcan najdeny:\n";
        std::cout << "ID: " << citizen->get_id()
                  << ", Meno: " << citizen->get_first_name()
                  << ", Priezvisko: " << citizen->get_last_name()
                  << ", Rodne cislo: " << citizen->get_birt_number()
                  << ", Adresa: " << citizen->get_address() << "\n";
    } else {
        std::cout << "Obcan s ID " << id << " nebol najdeny.\n";
    }
}

// Aktualizacia udajov obcana
void update_citizen() {
    std::cout << "\n===== AKTUALIZACIA OBCANA =====\n";
    int id = get_int_input("Zadajte ID obcana na aktualizaciu: ");

    auto citizen = find_citizen_by_id(id);
    if (!citizen) {
        std::cout << "Obcan s ID " << id << " nebol najdeny.\n";
        return;
    }

    std::string first_name, last_name, birth_number, address;

    std::cout << "Aktualne udaje:\n";
    std::cout << "Meno: " << citizen->get_first_name() << "\n";
    std::cout << "Priezvisko: " << citizen->get_last_name() << "\n";
    std::cout << "Rodne cislo: " << citizen->get_birt_number() << "\n";
    std::cout << "Adresa: " << citizen->get_address() << "\n";

    std::cout << "\nZadajte nove udaje (prazdny vstup pre ponechanie povodnej hodnoty):\n";

    std::cout << "Nove meno: ";
    std::getline(std::cin, first_name);
    if (first_name.empty()) first_name = citizen->get_first_name();

    std::cout << "Nove priezvisko: ";
    std::getline(std::cin, last_name);
    if (last_name.empty()) last_name = citizen->get_last_name();

    std::cout << "Nove rodne cislo: ";
    std::getline(std::cin, birth_number);
    if (birth_number.empty()) birth_number = citizen->get_birt_number();

    std::cout << "Nova adresa: ";
    std::getline(std::cin, address);
    if (address.empty()) address = citizen->get_address();

    // Aktualizacia
    citizen->update_info(first_name, last_name, birth_number, address);

    std::cout << "Udaje obcana boli uspesne aktualizovane.\n";
}

void delete_citizen() {
    std::cout << "\n===== VYMAZANIE OBCANA =====\n";
    int id = get_int_input("Zadajte ID obcana na vymazanie: ");

    auto citizen_to_delete = find_citizen_by_id(id);

    if (citizen_to_delete) {
        int index = citizens.find_index(citizen_to_delete);
        if (index >= 0) {
            citizens.pop_index(index);
            std::cout << "Obcan s ID " << id << " bol uspesne vymazany.\n";
        }
    } else {
        std::cout << "Obcan s ID " << id << " nebol najdeny.\n";
    }
}

// Vytvorenie noveho pozemku
std::shared_ptr<Plot> create_plot(const std::string& type, int id, double land_area) {
    if (type == "1" || type == "Orna poda") {
        return std::make_shared<PLOT_Orna_poda>(id, land_area);
    } else if (type == "2" || type == "Chmelnica") {
        return std::make_shared<PLOT_Chmelnica>(id, land_area);
    } else if (type == "3" || type == "Vinice") {
        return std::make_shared<PLOT_Vinice>(id, land_area);
    } else if (type == "4" || type == "Zahrady") {
        return std::make_shared<PLOT_Zahrady>(id, land_area);
    } else if (type == "5" || type == "Ovocne sady") {
        return std::make_shared<PLOT_Ovocne_sady>(id, land_area);
    } else if (type == "6" || type == "Trvale travne porasty") {
        return std::make_shared<PLOT_Trvale_travne_porasty>(id, land_area);
    } else if (type == "7" || type == "Lesne pozemky") {
        return std::make_shared<PLOT_Lesne_pozemky>(id, land_area);
    } else if (type == "8" || type == "Vodne plochy") {
        return std::make_shared<PLOT_Vodne_plochy>(id, land_area);
    } else if (type == "9" || type == "Zastavane plochy a nadvoria") {
        return std::make_shared<PLOT_Zastavane_plochy_a_nadvoria>(id, land_area);
    } else if (type == "10" || type == "Ostatne plochy") {
        return std::make_shared<PLOT_Ostatne_plochy>(id, land_area);
    } else if (type == "11" || type == "Ostatne polnohospodarske plochy") {
        return std::make_shared<PLOT_Ostatne_polnohospodarske_plochy>(id, land_area);
    } else {
        std::cerr << "CHYBA: Neznamy typ pozemku: " << type << "\n";
        return nullptr;
    }
}

// Zobrazenie typov pozemkov
void show_plot_types() {
    std::cout << "Dostupne typy pozemkov:\n";
    std::cout << "1. Orna poda\n";
    std::cout << "2. Chmelnica\n";
    std::cout << "3. Vinice\n";
    std::cout << "4. Zahrady\n";
    std::cout << "5. Ovocne sady\n";
    std::cout << "6. Trvale travne porasty\n";
    std::cout << "7. Lesne pozemky\n";
    std::cout << "8. Vodne plochy\n";
    std::cout << "9. Zastavane plochy a nadvoria\n";
    std::cout << "10. Ostatne plochy\n";
    std::cout << "11. Ostatne polnohospodarske plochy\n";
}

// Pridanie pozemku obcanovi
void add_plot_to_citizen() {
    std::cout << "\n===== PRIDANIE POZEMKU OBCANOVI =====\n";
    int citizen_id = get_int_input("Zadajte ID obcana: ");

    auto citizen = find_citizen_by_id(citizen_id);
    if (!citizen) {
        std::cout << "Obcan s ID " << citizen_id << " nebol najdeny.\n";
        return;
    }

    show_plot_types();
    std::string type_choice;
    std::cout << "Zvolte typ pozemku (1-11): ";
    std::getline(std::cin, type_choice);

    double land_area = get_double_input("Zadajte vymeru pozemku (m2): ");

    auto new_plot = create_plot(type_choice, next_plot_id++, land_area);
    if (new_plot) {
        citizen->add_plot(new_plot);
        std::cout << "Pozemok bol uspesne pridany obcanovi s ID: " << citizen_id
                  << " (ID pozemku: " << new_plot->get_id() << ")\n";
    } else {
        std::cout << "Nepodarilo sa vytvorit pozemok. Skontrolujte zadane udaje.\n";
    }
}

// Zobrazenie pozemkov obcana
void view_citizen_plots() {
    std::cout << "\n===== ZOZNAM POZEMKOV OBCANA =====\n";
    int citizen_id = get_int_input("Zadajte ID obcana: ");

    auto citizen = find_citizen_by_id(citizen_id);
    if (!citizen) {
        std::cout << "Obcan s ID " << citizen_id << " nebol najdeny.\n";
        return;
    }

    if (citizen->has_no_plots()) {
        std::cout << "Obcan nema evidovane ziadne pozemky.\n";
        return;
    }

    std::cout << "Pozemky obcana " << citizen->get_first_name() << " " << citizen->get_last_name() << ":\n";

    auto current = citizen->get_plots().get_head();
    while (current) {
        auto plot = current->get_data();
        std::cout << "ID: " << plot->get_id()
                  << ", Typ: " << plot->get_type_name()
                  << ", Vymera: " << plot->get_land_area() << " m2"
                  << ", Rocna dan: " << plot->calculate_tax() << " eur\n";
        current = current->get_next();
    }
}

// Najdenie pozemku obcana pomocou ID
std::shared_ptr<Plot> find_plot_by_id(std::shared_ptr<Citizen>& citizen, int plot_id) {
    auto current = citizen->get_plots().get_head();
    while (current) {
        auto plot = current->get_data();
        if (plot->get_id() == plot_id) {
            return plot;
        }
        current = current->get_next();
    }
    return nullptr;
}

// Aktualizacia pozemku
void update_plot() {
    std::cout << "\n===== AKTUALIZACIA POZEMKU =====\n";
    int citizen_id = get_int_input("Zadajte ID obcana: ");

    auto citizen = find_citizen_by_id(citizen_id);
    if (!citizen) {
        std::cout << "Obcan s ID " << citizen_id << " nebol najdeny.\n";
        return;
    }

    int plot_id = get_int_input("Zadajte ID pozemku: ");

    // Najdeme stary pozemok
    auto old_plot = find_plot_by_id(citizen, plot_id);
    if (!old_plot) {
        std::cout << "Pozemok s ID " << plot_id << " nebol najdeny.\n";
        return;
    }

    // Nájdeme index stareho pozemku
    int index = citizen->get_plots().find_index(old_plot);
    if (index < 0) {
        std::cout << "Chyba pri hladani indexu pozemku.\n";
        return;
    }

    std::cout << "Aktualne udaje pozemku:\n";
    std::cout << "ID: " << old_plot->get_id() << "\n";
    std::cout << "Typ: " << old_plot->get_type_name() << "\n";
    std::cout << "Vymera: " << old_plot->get_land_area() << " m2\n";

    char update_type;
    std::cout << "\nChcete zmenit typ pozemku? (a/n): ";
    std::cin >> update_type;
    clear_input_buffer();

    if (update_type == 'a' || update_type == 'A') {
        show_plot_types();
        int type_number = get_int_input("Zvolte novy typ pozemku (1-11): ");
        std::string type_choice = std::to_string(type_number);

        double land_area = get_double_input("Zadajte novu vymeru pozemku (m2): ");

        // Vytvorime novy pozemok so starym ID
        auto new_plot = create_plot(type_choice, plot_id, land_area);
        if (new_plot) {
            // Odstranime stary pozemok a vlozime novy
            citizen->remove_plot_by_index(index);

            if (index == 0) {
                citizen->add_plot(new_plot);
            } else {
                citizen->insert_plot_after_index(index - 1, new_plot);
            }

            std::cout << "Pozemok bol uspesne aktualizovany.\n";
        } else {
            std::cout << "Nepodarilo sa aktualizovat pozemok. Skontrolujte zadane udaje.\n";
        }
    } else {
        // Aktualizacia len vymery
        double land_area = get_double_input("Zadajte novu vymeru pozemku (m2): ");

        old_plot->set_land_area(land_area);
        std::cout << "Vymera pozemku bola uspesne aktualizovana.\n";
    }
}

// Vymazanie pozemku
void delete_plot() {
    std::cout << "\n===== VYMAZANIE POZEMKU =====\n";
    int citizen_id = get_int_input("Zadajte ID obcana: ");

    auto citizen = find_citizen_by_id(citizen_id);
    if (!citizen) {
        std::cout << "Obcan s ID " << citizen_id << " nebol najdeny.\n";
        return;
    }

    int plot_id = get_int_input("Zadajte ID pozemku na vymazanie: ");

    // najdeme index pozemku v zozname
    auto plot = find_plot_by_id(citizen, plot_id);
    if (!plot) {
        std::cout << "Pozemok s ID " << plot_id << " nebol najdeny.\n";
        return;
    }
    int index = citizen->get_plots().find_index(plot);

    if (index >= 0) {
        citizen->remove_plot_by_index(index);
        std::cout << "Pozemok s ID " << plot_id << " bol uspesne vymazany.\n";
    } else {
        std::cout << "Chyba pri mazani pozemku.\n";
    }
}