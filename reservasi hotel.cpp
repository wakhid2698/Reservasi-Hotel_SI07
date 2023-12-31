#include <iostream>
#include <string>
using namespace std;

const int MAX_ROOMS = 10;

struct Guest {
    string name;
    int roomNumber;
};

struct Node {
    Guest guest;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(NULL) {}

    void push(Guest* guest) {
        Node* newNode = new Node;
        newNode->guest = *guest;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void display() {
        Node* current = top;
        while (current != NULL) {
            cout << "Nama: " << current->guest.name << ", Kamar: " << current->guest.roomNumber << endl;
            current = current->next;
        }
    }

    ~Stack() {
        while (top != NULL) {
            pop();
        }
    }
};

class Hotel {
private:
    Guest* rooms[MAX_ROOMS];
    Node* checkIns;
    Node* checkOuts;
    Stack reservations;  // Tambahkan stack untuk merepresentasikan kamar yang dipesan

public:
    Hotel() {
        for (int i = 0; i < MAX_ROOMS; ++i) {
            rooms[i] = NULL;
        }
        checkIns = NULL;
        checkOuts = NULL;
    }

    // Menambahkan fungsi pengurutan (Bubble Sort)
    void bubbleSortRooms() {
        for (int i = 0; i < MAX_ROOMS - 1; ++i) {
            for (int j = 0; j < MAX_ROOMS - i - 1; ++j) {
                if (rooms[j] != NULL && rooms[j + 1] != NULL && rooms[j]->name > rooms[j + 1]->name) {
                    // Tukar elemen jika nama tamu pada kamar ke-j lebih besar dari nama tamu pada kamar ke-(j+1)
                    Guest* temp = rooms[j];
                    rooms[j] = rooms[j + 1];
                    rooms[j + 1] = temp;
                }
            }
        }
    }

    bool displayRooms() {
        bubbleSortRooms();  // Memanggil fungsi pengurutan
        cout << "Daftar Kamar (Diurutkan):\n";
        bool isEmpty = true;
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i] == NULL) {
                cout << "Kamar " << i + 1 << ": Kosong\n";
            } else {
                cout << "Kamar " << i + 1 << ": " << rooms[i]->name << endl;
                isEmpty = false;
            }
        }
        return !isEmpty;
    }

    bool checkIn() {
        string name;
        cout << "Masukkan nama tamu: ";
        cin >> name;

        int availableRoom = findAvailableRoom();
        if (availableRoom != -1) {
            rooms[availableRoom] = new Guest{name, availableRoom + 1};
            addToCheckIns(rooms[availableRoom]);
            cout << name << " berhasil check-in ke kamar " << availableRoom + 1 << endl;
            reservations.push(rooms[availableRoom]);  // Tambahkan kamar ke stack reservations
            return true;
        } else {
            cout << "Maaf, tidak ada kamar kosong saat ini.\n";
            return false;
        }
    }

    int findAvailableRoom() {
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i] == NULL) {
                return i;
            }
        }
        return -1;
    }

    bool checkOut() {
        int room;
        cout << "Masukkan nomor kamar untuk check-out: ";
        cin >> room;

        if (room >= 1 && room <= MAX_ROOMS) {
            if (rooms[room - 1] != NULL) {
                addToCheckOuts(rooms[room - 1]);
                reservations.pop();  // Hapus kamar dari stack reservations
                delete rooms[room - 1];
                rooms[room - 1] = NULL;
                cout << "Check-out dari kamar " << room << " berhasil.\n";
                return true;
            } else {
                cout << "Kamar tersebut sudah kosong.\n";
                return false;
            }
        } else {
            cout << "Nomor kamar tidak valid.\n";
            return false;
        }
    }

    void addToCheckIns(Guest* guest) {
        Node* newNode = new Node;
        newNode->guest = *guest;
        newNode->next = checkIns;
        checkIns = newNode;
    }

    void addToCheckOuts(Guest* guest) {
        Node* newNode = new Node;
        newNode->guest = *guest;
        newNode->next = checkOuts;
        checkOuts = newNode;
    }

    bool displayCheckIns() {
        Node* current = checkIns;
        cout << "Daftar Check-in:\n";
        bool isEmpty = true;
        while (current != NULL) {
            cout << "Nama: " << current->guest.name << ", Kamar: " << current->guest.roomNumber << endl;
            current = current->next;
            isEmpty = false;
        }
        return !isEmpty;
    }

    bool displayCheckOuts() {
        Node* current = checkOuts;
        cout << "Daftar Check-out:\n";
        bool isEmpty = true;
        while (current != NULL) {
            cout << "Nama: " << current->guest.name << ", Kamar: " << current->guest.roomNumber << endl;
            current = current->next;
            isEmpty = false;
        }
        return !isEmpty;
    }

    ~Hotel() {
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i] != NULL) {
                delete rooms[i];
            }
        }
        Node* current = checkIns;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        current = checkOuts;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    Hotel hotel;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tampilkan Ketersediaan Kamar\n";
        cout << "2. Check-in\n";
        cout << "3. Check-out\n";
        cout << "4. Tampilkan Check-in\n";
        cout << "5. Tampilkan Check-out\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayRooms();
                break;
            case 2:
                hotel.checkIn();
                break;
            case 3:
                hotel.checkOut();
                break;
            case 4:
                hotel.displayCheckIns();
                break;
            case 5:
                hotel.displayCheckOuts();
                break;
            case 6:
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 6);

    return 0;
}

