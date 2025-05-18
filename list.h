#ifndef LIST_H
#define LIST_H

#include <memory>
#include <iostream>


template<typename T>
class ListNode {
    std::shared_ptr<T> data;
    std::shared_ptr<ListNode> next;

public:
    // konstruktor
    ListNode(const std::shared_ptr<T>& data) : data(data), next(nullptr) {}

    std::shared_ptr<T> get_data() const { return data; }
    std::shared_ptr<ListNode> get_next() const { return next; }
    void set_next(const std::shared_ptr<ListNode>& node) { next = node; }
};

template<typename T>
class LinkedList {
    std::shared_ptr<ListNode<T>> head;

public:
    // vrati true ak je zoznam prazdny
    bool is_empty() const {
        return head == nullptr;
    }

    // vrati ukazovatel na prvy uzol
    std::shared_ptr<ListNode<T>> get_head() const {
        return head;
    }

    // vlozi novy prvok na zaciatok zoznamu
    void push_front(const std::shared_ptr<T>& value) {
        if (!value) {
            std::cerr << "CHYBA: Pridavana hodnota je null.\n";
            return;
        }
        auto new_node = std::make_shared<ListNode<T>>(value);
        new_node->set_next(head);
        head = new_node;
    }

    // vymaze prvy prvok v zozname, stary uzol zanikne vdaka shared_ptr
    void pop_front() {
        if (is_empty()) {
            std::cerr << "CHYBA: Zoznam je prazdny, nie je co odstranit.\n";
            return;
        }
        head = head->get_next();
    }

    void pop_index(int index) {
        if (index < 0) {
            std::cerr << "CHYBA: Index nemoze byt zaporny.\n";
            return;
        }

        if (is_empty()) {
            std::cerr << "CHYBA: Zoznam je prazdny, nie je co odstranit.\n";
            return;
        }

        if (index == 0) {
            pop_front();
            return;
        }

        auto current = head;
        int current_index = 0;

        while (current && current_index < index - 1) {
            current = current->get_next();
            current_index++;
        }

        if (!current || !current->get_next()) {
            std::cerr << "CHYBA: Index je mimo rozsahu zoznamu.\n";
            return;
        }

        current->set_next(current->get_next()->get_next());
    }

    //najde index podla pointeru
    int find_index(const std::shared_ptr<T>& value) const {
        if (!value) {
            std::cerr << "CHYBA: Hladana hodnota je null.\n";
            return -1;
        }

        auto current = head;
        int index = 0;

        while (current) {
            if (current->get_data() == value) {
                return index;
            }
            current = current->get_next();
            index++;
        }

        std::cerr << "CHYBA: Hladana hodnota sa v zozname nenachadza.\n";
        return -1;
    }

    // vlozi novy prvok za uzol na danom indexe
    void insert_after_index(int index, const std::shared_ptr<T>& value) {
        if (index < 0) {
            std::cerr << "CHYBA: Index nemoze byt zaporny.\n";
            return;
        }

        if (!value) {
            std::cerr << "CHYBA: Pridavana hodnota je null.\n";
            return;
        }

        auto current = head;
        int current_index = 0;

        while (current && current_index < index) {
            current = current->get_next();
            current_index++;
        }

        if (!current) {
            std::cerr << "CHYBA: Index je mimo rozsahu zoznamu.\n";
            return;
        }

        auto new_node = std::make_shared<ListNode<T>>(value);
        new_node->set_next(current->get_next());
        current->set_next(new_node);
    }

    // vlozi novy node za dany node, ak node neexistuje, vypise chybu
    void insert_after(const std::shared_ptr<ListNode<T>>& node, const std::shared_ptr<T>& value) {
        if (!node) {
            std::cerr << "CHYBA: Zadany uzol je null. Neda sa vlozit prvok.\n";
            return;
        }
        if (!value) {
            std::cerr << "CHYBA: Pridavana insert hodnota je null.\n";
            return;
        }
        auto new_node = std::make_shared<ListNode<T>>(value);
        new_node->set_next(node->get_next());
        node->set_next(new_node);
    }

    // vypise cely zoznam pomocou get_id(), predpoklada sa ze typ T ma metodu get_id()
    void print_all() const {
        if (is_empty()) {
            std::cout << "Zoznam je prazdny.\n";
            return;
        }

        auto current = head;
        while (current) {
            if (current->get_data()) {
                std::cout << current->get_data()->get_id() << '\n';
            } else {
                std::cerr << "CHYBA: Uzol obsahuje null data.\n";
            }
            current = current->get_next();
        }
    }
};

#endif // LIST_H