#include <iostream>
#include <string>
using namespace std;

//Blog
//https://novemberfirst.tistory.com/32 : class와 struct의 차이점
//https://chanhuiseok.github.io/posts/algo-37/ string 사용법
//https://velog.io/@sw801733/C-%EB%AC%B8%EC%9E%90%EC%97%B4-%EC%9E%85%EB%A0%A5-%EB%B0%9B%EA%B8%B0 문자열 입력 받기
//김호준 교수님 데이터 구조 강의 slide 28Heap01



//일단 heap을 만든다.
// insert 할 때마다 , min-heapify 적용한다.

// Show message
  const  string message = 
  "\n********** MENU ********** \n"
  "I : Insert new element into queue. \n"
  "D : Delete element with smallest key from queue.\n"
  "C : Delete key of element in queue.\n"
  "P : Print out all elements in queue.\n"
  "Q : Quit \n\n"
  "Choose menu :";

// Define element class
class element {
  public:
    int id; // Key
    string name; //at most 10 characters
    string school; // "Handong" , "Doodong" , "Sedong"
    void set_data(int i , string n , string s);
};

void element::set_data(int i, string n , string s){
  id = i;
  name = n ;
  school = s;
}

#define Heap_Size 30+1 //According to problem conditions. Heap Size is30 because I am goona vacate index 0
// Define heap class
class set{
  int e_size; // number of elements

  public :
    element Heap[Heap_Size]; // make Heap
    set(); // e_size = 0
    int set_size(); // return elements size  --> 현재 원소수 조회 ,ADT로 인해 e_size는 private 원소 
    bool heap_full(); // e_size >= Heap_Size - 1 ? 인지 판단
    bool heap_empty(); // e_size == 0 ? 인지 판단
    void MIN_HEAPIFY(set S); // Make heap to min heap.
    void INSERT(set &S , element x); //inserts element x into set S.
    element MINIMUM(set S); //returns element of S with largest key.
    element EXTRACT_MIN(set &S); // removes and returns element of S with largest key.
    void DECREASE_KEY(set &S, element &x , int k); // decreases value of element x's key to k.
    void PRINT_ALL(set S); // Print all elements in queue.
};

//Constructor
set::set(){
  e_size = 0;
}

//element의 개수가 Heap size보다 큰지 작은지 판단
bool set::heap_full(){
  if(e_size >= Heap_Size-1)
    return true;
  else
    return false;
}

//To get to private variable.
int set::set_size(){
  return e_size;
}

//Make Heap to Min Heap
void set::MIN_HEAPIFY(set S){
  int tmp_key;
  int child = 2;
  element tmp_element;

  tmp_element = S.Heap[1];
  tmp_key = S.Heap[1].id;
  
  while(child <= e_size){
    if((child < e_size) && S.Heap[child].id > S.Heap[child+1].id)
      child++;
    if(tmp_key < S.Heap[child].id)
      break;
    else{
      S.Heap[child/2] = S.Heap[child];
      child *=2;
    }
  }
  S.Heap[child/2] = tmp_element;
}

// -----  Inserts element x into set S. -----
// Increase by 1 of set size.
// if parent key > new key then, switch parent and new element.
// Confirm the 'place to put the element' as the current location.
// put the new element to confirmed place.
void set::INSERT(set &S, element x){
  string new_name;
  int new_id;
  string new_school;

  cout << "Enter name of element:";
  cin >> new_name;
  cout << "Enter id of element:";
  cin >> new_id;
  cout << "Enter school of element:";
  cin >> new_school;
  x.set_data(new_id,new_name,new_school); // Add element to set

  int k;
  e_size++;
  k = e_size;

  while((k !=1) && (x.id < S.Heap[k/2].id))
  {
    S.Heap[k] = S.Heap[k/2];
    k = k/2;
  }

  S.Heap[k] = x;

  cout << "New element [" << S.Heap[k].name << ", " << S.Heap[k].id << ", " << S.Heap[k].school << "]" << "is inserted" << endl;

} 

// ----- Returns element of S with smallest key. -----
element set::MINIMUM(set S){
  return S.Heap[1];
}  

// ----- Removes and returns element of S with smallest key. -----
// Prepare return. To save root element in temp element
// Save last element to adjust place.
// Reduce size by 1.
// From root's element to last's element repeat follow steps, then find last element's place.
//  step 1 If there are no more child , determine the place would be parent's location.
//  step 2 Compare left child and right child , choose smaller key node.
//  step 3 Compare 2's key with child key. If child's key is bigger then determine the place.
//  step 4 If child's key is smaller, then swap parent and child. and go to step 1.
// Put the last element in the determined place.
// ----- Return the saved root element. -----
element set::EXTRACT_MIN(set &S){

  element temp_root = S.MINIMUM(S); // root element (return value)
  element temp_last = S.Heap[e_size]; // last element 
  int parent = 1; // root place
  int child = 2; //root's left child place
  e_size --; //Reduce size by 1

  //step 1 ~ 4
  while(child <= e_size) { //from root to last element
    if((child < e_size) && (S.Heap[child].id > S.Heap[child+1].id)) // Compare left child and right child.
      child ++; // If right smaller than left, choose right child.
    if(temp_last.id <= S.Heap[child].id) //If last element is smaller than child element then break.
      break;
    S.Heap[parent] = S.Heap[child]; // If child element smaller than last element. Swap parent element and child element.
    parent = child; // Go down.
    child *= 2; // Go down.
  }
  S.Heap[parent] = temp_last; // Save temp_last into finded place.
  return temp_root; //return root element. --> The minimum element.

}

// ----- decreases value of element x's key to k. -----
void set::DECREASE_KEY(set &S, element &x , int k){

  x.set_data(k, x.name , x.school);
  S.Heap[k] = x;
  S.MIN_HEAPIFY();
  cout <<"[" << S.Heap[k].name << ", " << S.Heap[k].id << ", " << S.Heap[k].school << "]" << endl;

}

// Print out all elements in queue.
void set::PRINT_ALL(set S){
  for(int i = 1 ; i <= S.set_size() ; i++){
    cout << "[" << S.Heap[i].name << ", " << S.Heap[i].id <<", " << S.Heap[i].school << "]" << endl;
  }
}




int main(){

int element_index;
int new_id;
char menu;
set s;
element e;

while(menu != 'Q'){

  cout << message;
  cin >> menu;

  switch(menu){
    case 'I':
      s.INSERT(s,e);
      break;
    case 'D':
      s.EXTRACT_MIN(s);
      break;
    case 'C':

      cout << "Enter index of element: " ;
      cin >> element_index;
      cout << "Enter id value: ";
      cin >> new_id;
      s.DECREASE_KEY(s,s.Heap[element_index],new_id);
      break;
    case 'P':
      s.PRINT_ALL(s);
      break;
    case 'Q':
      cout << "Thank you. Bye!";
      return 0;
  }
}




}