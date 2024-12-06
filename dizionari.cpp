#include <iostream>
#include <string>
#include <optional>

template <typename T>
class HashMap {
private:
    static const int SIZE = 10;  // Dimensione della tabella hash
    struct Node {
        std::string key;  // La chiave di ricerca
        T value;          // Il valore associato alla chiave
        bool isOccupied = false;  // Indica se la cella è occupata
        bool isDeleted = false;   // Indica se la chiave è stata eliminata
    };

    Node table[SIZE];  // La tabella hash, un array di nodi

    // Funzione di hash per calcolare l'indice in base alla chiave
    int hashFunction(const std::string& key) const {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % SIZE;  // Moltiplica per 31 e calcola il modulo
        }
        return hashValue;  // Restituisce l'indice calcolato
    }

    // Trova la posizione della chiave nella tabella
    int findSlot(const std::string& key) const {
        int index = hashFunction(key);  // Ottieni l'indice iniziale

        // Cerca una posizione disponibile o una chiave corrispondente
        while (table[index].isOccupied && !table[index].isDeleted && table[index].key != key) {
            index = (index + 1) % SIZE;  // Prova la posizione successiva
        }
        return index;  // Restituisce l'indice trovato
    }

public:
    // Inserisce una nuova coppia chiave-valore
    void insert(const std::string& key, const T& value) {
        int index = findSlot(key);  // Trova il posto per la chiave
        table[index].key = key;     // Imposta la chiave
        table[index].value = value; // Imposta il valore
        table[index].isOccupied = true;  // La posizione è occupata
        table[index].isDeleted = false; // La chiave non è eliminata
    }

    // Recupera il valore associato a una chiave, se esiste
    std::optional<T> retrieve(const std::string& key) const {
        int index = findSlot(key);  // Trova il posto della chiave

        // Se la chiave è presente e non è stata eliminata, restituisci il valore
        if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key) {
            return table[index].value;
        }
        return std::nullopt;  // Restituisce nullopt se la chiave non è trovata
    }

    // Cancella la chiave dalla tabella
    void remove(const std::string& key) {
        int index = findSlot(key);  // Trova il posto della chiave

        // Se la chiave è presente, segna la posizione come eliminata
        if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key) {
            table[index].isDeleted = true;  // Segna la chiave come eliminata
            std::cout << "Chiave '" << key << "' eliminata con successo.\n";
        } else {
            std::cout << "Chiave '" << key << "' non trovata per l'eliminazione.\n";
        }
    }

    // Verifica se una chiave esiste nella tabella
    bool contains(const std::string& key) const {
        int index = findSlot(key);  // Trova la posizione della chiave
        return table[index].isOccupied && !table[index].isDeleted && table[index].key == key;
    }

    // Stampa il contenuto della tabella
    void print() const {
        for (int i = 0; i < SIZE; ++i) {
            // Se la posizione è occupata e non è eliminata, stampa la chiave e il valore
            if (table[i].isOccupied && !table[i].isDeleted) {
                std::cout << "Indice " << i << ": " << table[i].key << " => " << table[i].value << "\n";
            }
        }
    }
};

int main() {
    HashMap<int> myHashMap;  // Crea un'istanza della classe HashMap con valori di tipo int

    std::cout << "Inserimento delle coppie chiave-valore:\n";
    myHashMap.insert("apple", 10);    // Aggiungi la chiave "apple" con valore 10
    myHashMap.insert("banana", 20);   // Aggiungi la chiave "banana" con valore 20
    myHashMap.insert("cherry", 30);   // Aggiungi la chiave "cherry" con valore 30
    myHashMap.insert("fig", 40);      // Aggiungi la chiave "fig" con valore 40
    myHashMap.insert("grape", 50);    // Aggiungi la chiave "grape" con valore 50

    std::cout << "\nContenuto della mappa:\n";
    myHashMap.print();  // Stampa il contenuto della tabella

    std::cout << "\nVerifica se 'banana' esiste nella mappa: " 
              << (myHashMap.contains("banana") ? "Sì" : "No") << std::endl;
    std::cout << "Verifica se 'orange' esiste nella mappa: "
              << (myHashMap.contains("orange") ? "Sì" : "No") << std::endl;

    std::cout << "\nRecupero del valore per 'banana':\n";
    if (auto value = myHashMap.retrieve("banana")) {
        std::cout << "Valore per 'banana': " << *value << std::endl;
    } else {
        std::cout << "Chiave 'banana' non trovata.\n";
    }

    std::cout << "\nRimozione della chiave 'banana':\n";
    myHashMap.remove("banana");  // Rimuove la chiave "banana"

    std::cout << "\nTentativo di rimuovere la chiave 'orange':\n";
    myHashMap.remove("orange");  // Tentativo di rimuovere una chiave non presente

    std::cout << "\nContenuto della mappa dopo le rimozioni:\n";
    myHashMap.print();  // Stampa di nuovo la mappa dopo la rimozione

    std::cout << "\nVerifica se 'banana' esiste nella mappa dopo la rimozione: " 
              << (myHashMap.contains("banana") ? "Sì" : "No") << std::endl;

    return 0;
}
