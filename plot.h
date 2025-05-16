#ifndef PLOT_H
#define PLOT_H
#include <string>

class Plot {
        int id;
        double land_area;
    protected:
        //Rozdielne pre kazdy druh pozemku
        [[nodiscard]] virtual double getTaxRate() const = 0;
        [[nodiscard]] virtual bool isBuildingLand() const { return false; }

    public:
        Plot(int id, double land_area);
        virtual ~Plot() = default;

        [[nodiscard]] int get_id() const {return this->id;}
        [[nodiscard]] double get_land_area() const {return this->land_area;}
        [[nodiscard]] virtual std::string getTypeName() const = 0;

        // Sadzba (€/m²/rok)
        virtual double calculate_tax() const {
            return land_area * getTaxRate();
        }

};

class PLOT_Orna_poda : public Plot {
    double tax_rate = 0.03;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Orna_poda(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Orna poda"; }
};

class PLOT_Chmelnica : public Plot {
    double tax_rate = 0.08;
    double special_tax_rate = 0.03;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Chmelnica(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Chmelnica"; }
    // Pozemok je pouzivany na pestovanie suroviny, pouzitelnej na vyrobu alkoholu, takze zvysime dan
    double calculate_tax() const override {
        return get_land_area() * (getTaxRate() + special_tax_rate);
    }
};

class PLOT_Vinice : public Plot {
    double tax_rate = 0.07;
    double special_tax_rate = 0.04;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Vinice(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Vinice"; }
    // Taktiez pouzitelne na vyrobu alkoholu, ale vino je hnusne takze zvysime dan este viac
    double calculate_tax() const override {
        return get_land_area() * (getTaxRate() + special_tax_rate);
    }
};

class PLOT_Zahrady : public Plot {
    double tax_rate = 0.03;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Zahrady(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Zahrady"; }
};

class PLOT_Ovocne_sady : public Plot {
    double tax_rate = 0.04;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Ovocne_sady(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Ovocne sady"; }
};

class PLOT_Trvale_travne_porasty : public Plot {
    double tax_rate = 0.01;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Trvale_travne_porasty(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Trvale travne porasty"; }
};

class PLOT_Lesne_pozemky : public Plot {
    double tax_rate = 0.02;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Lesne_pozemky(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Lesne pozemky"; }
};

class PLOT_Vodne_plochy : public Plot {
    double tax_rate = 0.09;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Vodne_plochy(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Vodne plochy"; }
};

class PLOT_Zastavane_plochy_a_nadvoria : public Plot {
    double tax_rate = 0.06;
    double getTaxRate() const override {return tax_rate;}
    bool isBuildingLand() const override { return true; }
public:
    PLOT_Zastavane_plochy_a_nadvoria(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Zastavane plochy a nadvoria"; }
};

class PLOT_Ostatne_plochy : public Plot {
    double tax_rate = 0.045;
    double getTaxRate() const override {return tax_rate;}
    bool isBuildingLand() const override { return true; }
public:
    PLOT_Ostatne_plochy(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Ostatne plochy"; }
};

class PLOT_Ostatne_polnohospodarske_plochy : public Plot {
    double tax_rate = 0.035;
    double getTaxRate() const override {return tax_rate;}
public:
    PLOT_Ostatne_polnohospodarske_plochy(int id, double land_area) : Plot(id, land_area){};
    std::string getTypeName() const override { return "Ostatne polnohospodarske plochy"; }
};

#endif //PLOT_H
