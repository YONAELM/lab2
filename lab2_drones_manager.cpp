#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}
DronesManager::~DronesManager() {
//    DroneRecord* last_record = last;
//    for (int i = size; i > 0; --i) {
//        last_record;
//    }
}
bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool are_equal = true;
	are_equal = are_equal && (lhs.droneID == rhs.droneID);
	return are_equal;
}

unsigned int DronesManager::get_size() const {
	return size;
}
bool DronesManager::empty() const {
	return (size == 0);
}
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if(!first) {
		return DroneRecord();
	} else if (index < 0 || index > size) {
	    return *getDroneRecord(size-1);
	} else {
        DroneRecord* cur = first;
        int position = 0;
        while (position != index) {
            cur = cur->next;
            position++;
        }
        return *cur;

	}
}

unsigned int DronesManager::search(DroneRecord value) const {
    if (size == 0) {
        return 0;
    } else {
        for (int i = 0; i < size; i++) {
            if (value == *getDroneRecord(i)) {
                return i;
            }
        }
        return size;
    }
}

void DronesManager::print() const {

    if (empty()) {
        cout << "There are no Drone Records to display.";
        return;
    }
    for(int i = 0; i < size; i++) {
        DroneRecord current_record = *getDroneRecord(i);
        cout << "Drone ID: " << current_record.droneID;
        cout << " Type: " << current_record.droneType;
        cout << " Manufacturer: " << current_record.manufacturer;
        cout << " Description: " << current_record.description;
        cout << " Range: " << current_record.range;
        cout << " Battery Type: " << current_record.batteryType;
        cout << " Year bought: " << current_record.yearBought;
        cout << endl;
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {

    DroneRecord* new_record = new DroneRecord(value);
    DroneRecord* current_record = first;
    bool inserted = false;

    if(!first || index > size){
        inserted = false;
    } else if(size == 0 && index ==0) {
        inserted = insert_front(value);
    }else if (size == index){
        inserted = insert_back(value);
    }else{

        int position = 0;

        while(position != index && current_record->next){
            position++;
            current_record = current_record->next;
        }

        DroneRecord* prev_record = current_record->prev;

        new_record->prev = prev_record;
        new_record->next = current_record;
        current_record->prev = new_record;


        if(prev_record){
            prev_record->next = new_record;
        }else{
            first = new_record;
        }

        size ++;
        inserted = true;
    }


    return inserted;
}

bool DronesManager::insert_front(DroneRecord value) {

    DroneRecord* new_record = new DroneRecord(value);
    bool inserted = false;

    if (!first) {
        first = new_record;
        last = first;
        size++;
        inserted = true;
    } else{
        first->prev = new_record;
        new_record->next = first;
        first = new_record;
        size++;
        inserted = true;
    }

    return inserted;
}

bool DronesManager::insert_back(DroneRecord value) {

    DroneRecord* new_record = new DroneRecord(value);
    bool inserted = false;

    if (!first) {
        first = new_record;
        last = first;
        size++;
        inserted = true;
    } else {
        last->next = new_record;
        new_record->prev = last;
        last = new_record;
        size++;
        inserted = true;
    }

    return inserted;
}

bool DronesManager::remove(unsigned int index) {
    //Can explain why dont have to check for when index = 0 and size = 0
    DroneRecord* current_record = first;
    bool removed = false;
    if (!first || index >= size){
        removed = false;

    }else if(size  == 1 && index == 0){//Delete the only element of the list
        first = NULL;
        removed = true;
    }else{

        int count = 0;
        while(index != count && current_record->next){
            current_record = current_record->next;
            count++;
        }

        if (current_record->next) {
            current_record->next->prev = current_record->prev;
        } else {
            last = current_record->prev;
        }

        if(current_record->prev) {
            current_record->prev->next = current_record->next;
        } else {
            first = current_record->next;
        }
        removed = true;
    }
    --size;
    delete current_record;
    current_record = NULL;

    return removed;
}
bool DronesManager::remove_front() {

    if(!first){
        return false;
    }else if (size  == 1) {
        delete first;
        first = NULL;
        last = NULL;
    } else{
        first = first->next;
        delete first->prev;
        first->prev = NULL;
    }
    --size;
    return true;
}
bool DronesManager::remove_back() {
    //PLEASE CHECK
    //Was not sure if we should delete DroneRecord or DroneManager
    if(!first){
        return false;
    }else if(size  == 1){
        delete last;
        last = NULL;
        first = NULL;
    }else{
        DroneRecord* end = first;
        while(end->next){
            end = end -> next;
        }
        last = end->prev;
        last->next = NULL;

        delete end;
        end = NULL;
    }
    --size;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    DroneRecord* new_record = new DroneRecord(value);
    DroneRecord* current_record = first;

    if(!first || index >= size){
        delete new_record;
        new_record = NULL;
        return false;
    }else if(size  == 1 && index == 0){
        first = new_record;
        last = first;
    }else{

        int count = 0;
        while(index != count){
            current_record = current_record -> next;
            count++;
        }
        new_record->prev = current_record->prev;
        new_record->next = current_record->next;
        if(new_record->prev) {
            new_record->prev->next = new_record;
        } else {
            first = new_record;
        }
        if(new_record->next) {
            new_record->next->prev = new_record;
        } else {
            last = new_record;
        }
    }

    delete current_record;
    current_record = NULL;
    return true;
}

bool DronesManager::reverse_list() {
    if(!first){
        return false;
    }else if (size == 1) {
        return true;
    } else{

        DroneRecord* current_record = first;
        DroneRecord* prev_record = first->prev;
        DroneRecord* next_record = first->next;
        int count = 0;
        //Decided not to use current_record -> next as condition
        //Cause we might miss the last case
        while(count < size){
            current_record->next = prev_record;
            current_record->prev = next_record;
            current_record = current_record->prev;
            if(current_record) {
                next_record = current_record->next;
                prev_record = current_record->prev;
            } else {
                last = first;
                first = prev_record->prev;
            }

            count ++;
        }
    }
    return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
    bool is_sorted_asc = true;
    if(!first){
        is_sorted_asc = false;
    } else if (!first->next){
        is_sorted_asc = true;
    }else{
        DroneRecord* current_record = first;
        while (current_record->next && is_sorted_asc){
            is_sorted_asc = is_sorted_asc && (current_record->droneID < current_record->next->droneID);
            current_record = current_record->next;
        }
    }
    return is_sorted_asc;
}
bool DronesManagerSorted::is_sorted_desc() const {
    bool is_sorted_desc = true;
    if(!first){
        is_sorted_desc = false;
    } else if (!first->next){
        is_sorted_desc = true;
    }else{
        DroneRecord* current_record = first;
        while (current_record->next && is_sorted_desc){
            is_sorted_desc = is_sorted_desc && (current_record->droneID > current_record->next->droneID);
            current_record = current_record->next;
        }
    }
    return is_sorted_desc;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {

    bool sorted_insert = false;
    if (is_sorted_asc()) {
        if(!first) {
            insert_front(val);
            sorted_insert = true;

        } else if(!first->next) {
            val.droneID < first->droneID ? insert_front(val) : insert_back(val);
            sorted_insert = true;
        } else{
            DroneRecord* current_record = first;
            int count = 0;
            while(current_record->next && !sorted_insert) {
                if (current_record->droneID < val.droneID && val.droneID < current_record->next->droneID) {
                    insert(val, count + 1);
                    sorted_insert = true;
                }
                count ++;
                current_record = current_record->next;
            }
        }
    }
	return sorted_insert;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    bool sorted_insert = false;
    if (is_sorted_desc()) {
        if(!first) {
            insert_front(val);
            sorted_insert = true;

        } else if(!first->next) {
            val.droneID > first->droneID ? insert_front(val) : insert_back(val);
            sorted_insert = true;
        } else{
            DroneRecord* current_record = first;
            int count = 0;
            while(current_record->next && !sorted_insert) {
                if (current_record->droneID > val.droneID && val.droneID > current_record->next->droneID) {
                    insert(val, count + 1);
                    sorted_insert = true;
                }
                count ++;
                current_record = current_record->next;
            }
        }
    }
    return sorted_insert;
}

void DronesManagerSorted::sort_asc() {
    if (size == 1) {
        return;
    }
    DroneRecord* current_record = first;
    int count = 0;
    while(count != size){
        if(current_record->droneID > current_record->next->droneID && current_record->next){
//                insert_front(current_record->next);
//                remove(count);
            //Cases
            // 1. Both last and first:  [2] - [1]                   -->     [1] - [2]
            // 2. Only last:            [1] - [3] - [2]             -->     [1] - [2] - [3]
            // 3. Only first:           [2] - [1] - [3]             -->     [1] - [2] - [3]
            // 4. No last no first:     [1] - [3] - [2] - [4]       -->     [1] - [2] - [3] - [4]
            // 1st case
            // Both last and first:  [2] - [1]  -->   [1] - [2]
            if (current_record == first && !current_record->next->next){
                //current_record is [2]
                DroneRecord* one_record = current_record->next;
                current_record->next = NULL;
                current_record->prev = one_record;
                one_record->next = current_record;
                one_record->prev = NULL;
                first = one_record;
                last = current_record;
            }
                // 2nd case
                // Only last:         [1] - [3] - [2]  -->  [1] - [2] - [3]
            else if (current_record != first && !current_record->next->next){
                //current_record is [3]
                DroneRecord* two_record = current_record->next;
                two_record->next = current_record;
                two_record->prev = current_record->prev;
                current_record->next = NULL;
                current_record->prev = two_record;
                last = current_record;
            }
                // 3rd case
                // Only first:     [2] - [1] - [3]  -->   [1] - [2] - [3]
            else if (current_record == first && current_record->next->next){
                //current_record is [2]
                DroneRecord* one_record = current_record->next;
                current_record->next = one_record->next;
                current_record->prev = one_record;
                one_record->next = current_record;
                one_record->prev = NULL;
                first = one_record;
            }
                // 4th case
                // No last no first:     [1] - [3] - [2] - [4]   -->   [1] - [2] - [3] - [4]
            else if (current_record != first && current_record->next->next){
                //current_record is [3]
                DroneRecord* two_record = current_record->next;
                DroneRecord* four_record = current_record->next->next;
                two_record->next = current_record;
                two_record->prev = current_record->prev;
                current_record->next = four_record;
                current_record->prev = two_record;
            }
            //Resetting the iterators
            count = 0;
            current_record = first;
        }else{
            count++;
            current_record = current_record->next;
        }
    }
}

void DronesManagerSorted::sort_desc() {
    DroneRecord* current_record = first;
    int count = 0;
    while(count != size){
        if(current_record->droneID < current_record->next->droneID){
            //Cases
            // 1. Both last and first:  [1] - [2]                   -->     [2] - [1]
            // 2. Only last:            [3] - [1] - [2]             -->     [3] - [2] - [1]
            // 3. Only first:           [2] - [3] - [1]             -->     [3] - [2] - [1]
            // 4. No last no first:     [4] - [2] - [3] - [1]       -->     [4] - [3] - [2] - [1]
            // 1st case
            // Both last and first:  [1] - [2]  -->   [2] - [1]
            if (current_record == first && !current_record->next->next){
                //current_record is [1]
                DroneRecord* two_record = current_record->next;
                current_record->next = NULL;
                current_record->prev = two_record;
                two_record->next = current_record;
                two_record->prev = NULL;
                first = two_record;
                last = current_record;
            }
                // 2nd case
                // Only last: [3] - [1] - [2]    -->     [3] - [2] - [1]
            else if (current_record != first && !current_record->next->next){
                //current_record is [1]
                DroneRecord* two_record = current_record->next;
                two_record->next = current_record;
                two_record->prev = current_record->prev;
                current_record->next = NULL;
                current_record->prev = two_record;
                last = current_record;
            }
                // 3rd case
                // Only first:  [2] - [3] - [1]     -->     [3] - [2] - [1]
            else if (current_record == first && current_record->next->next){
                //current_record is [2]
                DroneRecord* three_record = current_record->next;
                current_record->next = three_record->next;
                current_record->prev = three_record;
                three_record->next = current_record;
                three_record->prev = NULL;
                first = three_record;
            }
                // 4th case
                // No last no first:     [4] - [2] - [3] - [1]      -->     [4] - [3] - [2] - [1]
            else if (current_record != first && current_record->next->next){
                //current_record is [2]
                DroneRecord* three_record = current_record->next;
                DroneRecord* one_record = current_record->next->next;
                three_record->next = current_record;
                three_record->prev = current_record->prev;
                current_record->next = one_record;
                current_record->prev = three_record;
            }
            //Resetting the iterators
            count = 0;
            current_record = first;
        }else{
            count++;
            current_record = current_record->next;
        }
    }
}

DronesManager :: DroneRecord* DronesManager :: getDroneRecord(unsigned int index) const {
    if (empty() || index < 0 || index >= size) {
        return NULL;
    } else {
        DroneRecord* cur = first;
        int position = 0;
        while (position != index) {
            cur = cur->next;
            position++;
        }
        return cur;
    }
}
