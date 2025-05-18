#ifndef CITIZEN_H
#define CITIZEN_H
#include "plot.h"
#include "list.h"


class Citizen {
    int id;
    std::string first_name;
    std::string last_name;
    std::string birth_number;
    std::string address;

    // zoznam pozemkov, ktoré občan vlastní
    LinkedList<Plot> plots;

    public:
    Citizen(int const & id, std::string const & first_name, std::string const & last_name,
        std::string const & birt_number, std::string const & address):
        id(id),
        first_name(first_name),
        last_name(last_name),
        birth_number(birt_number),
        address(address){};

    ~Citizen() = default;

    //Gettery
    int get_id() const {return this->id;}
    std::string get_first_name() const {return this->first_name;}
    std::string get_last_name() const {return this->last_name;}
    std::string get_birth_number() const {return this->birth_number;}
    std::string get_address() const {return this->address;}

    // Aktualizacia osobnych udajov obcana
    void update_info(std::string const & first_name, std::string const & last_name,
                     std::string const & birth_number, std::string const & address) {
        this->first_name = first_name;
        this->last_name = last_name;
        this->birth_number = birth_number;
        this->address = address;
    }

    // Manipulacia s pozemkami

    //vrati referenciu na sukromny clen plots
    LinkedList<Plot>& get_plots() { return plots; }

    // prida pozemok na zaciatok
    void add_plot(const std::shared_ptr<Plot>& plot) {
        plots.push_front(plot);
    }

    // vymaze pozemok podla indexu
    void remove_plot_by_index(int index) {
        plots.pop_index(index);
    }

    // vypise vsetky pozemky
    void print_all_plots() const {
        plots.print_all();
    }

    // vlozi pozemok za dany index
    void insert_plot_after_index(int index, const std::shared_ptr<Plot>& plot) {
        plots.insert_after_index(index, plot);
    }

    // najde index pozemku (podla pointeru)
    int find_plot_index(const std::shared_ptr<Plot>& plot) const {
        return plots.find_index(plot);
    }

    // zisti ci obcan nema ziadny pozemok
    bool has_no_plots() const {
        return plots.is_empty();
    }

    // odstrani prvy pozemok
    void remove_first_plot() {
        plots.pop_front();
    }

};



#endif //CITIZEN_H
