#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <utility>
#include <chrono>
using namespace std;

bool isFloat(string str);
bool isAlph(string str);
enum Color { RED, BLACK };

class Movie {
public:
	Movie();
	Movie(string _genres, float _popularity, string _revenue, int _runtime, string _title, string actor1, string actor2, string actor3, string actor4, string actor5, string director, string producer, string screenplay, string editor);
	void operator=(Movie* next);
	Movie(const Movie& next);
	Movie& operator=(Movie&& next);
	Movie& operator=(Movie& next);
	void PrintMovie();
	void setGenres(string _genres);
	void setPop(string _pop);
	void setRevenue(string _revenue);
	void setRuntime(string _runtime);
	void setTitle(string _title);
	void setActor1(string _actor1);
	void setActor2(string _actor2);
	void setActor3(string _actor3);
	void setActor4(string _actor4);
	void setActor5(string _actor5);
	void setDirector(string _director);
	void setProducer(string _producer);
	void setScreenplay(string _screenplay);
	void setEditor(string _editor);
	//for tree
	Movie* left, * right, * parent;
	bool color;
public:
	// from Clean in order listed
	//int idC;
	//int budget;
	string genres;
	//string imdb_id;
	//string original_language;
	//string original_title;
	//string overview;
	float popularity;
	//string production_company;
	//string production_country;
	//string release_date;
	string revenue;
	int runtime;
	//string spoken_languages;
	//string status;
	//string tagline;
	string title;
	//float vote_average;
	//int vote_count;
	//int production_companies_number;
	//int production_countries_number;
	//int spoken_languages_number;

	// from Raw in order listed
	//int idR;
	string actor1_name;
	//int actor1_gender; // 0 unknown, 1 female, 2 male
	string actor2_name;
	//int actor2_gender;
	string actor3_name;
	//int actor3_gender;
	string actor4_name;
	//int actor4_gender;
	string actor5_name;
	//int actor5_gender;
	//int actor_number;
	string director_name;
	//int director_gender;
	//int director_number;
	string producer_name;
	//int producer_number;
	string screenplay_writer_name;
	string editor_name;
};

Movie::Movie(const Movie& next) {
	genres = next.genres;
	popularity = next.popularity;
	revenue = next.revenue;
	runtime = next.runtime;
	title = next.title;
	actor1_name = next.actor1_name;
	actor2_name = next.actor2_name;
	actor3_name = next.actor3_name;
	actor4_name = next.actor4_name;
	actor5_name = next.actor5_name;
	director_name = next.director_name;
	producer_name = next.producer_name;
	screenplay_writer_name = next.screenplay_writer_name;
	editor_name = next.editor_name;
}

Movie& Movie::operator=(Movie& next)
{
	genres = next.genres;
	popularity = next.popularity;
	revenue = next.revenue;
	runtime = next.runtime;
	title = next.title;
	actor1_name = next.actor1_name;
	actor2_name = next.actor2_name;
	actor3_name = next.actor3_name;
	actor4_name = next.actor4_name;
	actor5_name = next.actor5_name;
	director_name = next.director_name;
	producer_name = next.producer_name;
	screenplay_writer_name = next.screenplay_writer_name;
	editor_name = next.editor_name;
	return *this;
}

Movie& Movie::operator=(Movie&& next)
{
	genres = next.genres;
	popularity = next.popularity;
	revenue = next.revenue;
	runtime = next.runtime;
	title = next.title;
	actor1_name = next.actor1_name;
	actor2_name = next.actor2_name;
	actor3_name = next.actor3_name;
	actor4_name = next.actor4_name;
	actor5_name = next.actor5_name;
	director_name = next.director_name;
	producer_name = next.producer_name;
	screenplay_writer_name = next.screenplay_writer_name;
	editor_name = next.editor_name;

	next.genres = "";
	next.popularity = 1.0;
	next.revenue = "";
	next.runtime = 1;
	next.title = "";
	next.actor1_name = "";
	next.actor2_name = "";
	next.actor3_name = "";
	next.actor4_name = "";
	next.actor5_name = "";
	next.director_name = "";
	next.producer_name = "";
	next.screenplay_writer_name = "";
	next.editor_name = "";

	return *this;
}

class HashTable {
public:
	//the number of bins in the table
	unsigned int capacity;
	//this is the array used for the hash table. The vector component is necessary for chaining
	vector<pair<string, Movie>>* arr = new vector<pair<string, Movie>>[capacity];
	//the number of movies added to the table
	unsigned int movieCount;

	//constructor
	HashTable(unsigned int capacity) {
		this->capacity = capacity;
	}

	//converts key to an index
	unsigned int Hash(string key) {
		unsigned int index = 0;

		for (int i = 0; i < key.size(); i++) {
			index += key[i];
		}

		index = index % capacity;
		return index;
	}

	//inserts a movie into the hash table
	void Insert(Movie movie) {
		pair<string, Movie> pair;
		pair.first = movie.title;
		pair.second = Movie(movie);
		arr[Hash(pair.first)].push_back(pair);

		//increment the movie count
		movieCount++;
	}

	//deletes a movie
	void Delete(Movie movie) {
		int index = Hash(movie.title);
		for (int i = 0; i < arr[index].size(); i++) {
			if (arr[index][i].first == movie.title) {
				arr[index].erase(arr[index].begin() + i);
			}
		}

		//decrement the movie count
		movieCount--;
	}

	//used to print out a movie's info
	void Print(Movie movie) {
		cout << "Genres: " << movie.genres << endl;
		cout << "Popularity: " << movie.popularity << endl;
		cout << "Revenue: " << movie.revenue << endl;
		cout << "Runtime: " << movie.runtime << endl;
		cout << "Title: " << movie.title << endl;
		cout << "Actor 1: " << movie.actor1_name << endl;
		cout << "Actor 2: " << movie.actor2_name << endl;
		cout << "Actor 3: " << movie.actor3_name << endl;
		cout << "Actor 4: " << movie.actor4_name << endl;
		cout << "Actor 5: " << movie.actor5_name << endl;
		cout << "Director: " << movie.director_name << endl;
		cout << "Producer: " << movie.producer_name << endl;
		cout << "Screenplay by: " << movie.screenplay_writer_name << endl;
		cout << "Editor: " << movie.editor_name << endl;
	}

	//this method is needed to search for a particular movie
	void SearchTitle(string title) {
		int index = Hash(title);
		bool printed = false;

		for (int i = 0; i < arr[index].size(); i++) {
			if (arr[index][i].second.title == title) {
				Print(arr[index][i].second);
				printed = true;
			}
		}

		if (!printed) {
			cout << "There are no documented movies with that genre." << endl;

		}
	}

	//this method is needed to search for a particular movie by genre
	void searchGenre(string genres) {
		bool printed = false;
		for (int i = 0; i < capacity; i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				if (arr[i][j].second.genres == genres) {
					Print(arr[i][j].second);
					printed = true;
				}
			}

		}
		if (!printed) {
			cout << "There are no documented movies with that genre." << endl;
		}

	}

	//this method is needed to search for a movie by actor
	void searchActor(string actor) {
		bool printed = false;

		for (int i = 0; i < capacity; i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				if (arr[i][j].second.actor1_name == actor ||
					arr[i][j].second.actor2_name == actor ||
					arr[i][j].second.actor3_name == actor ||
					arr[i][j].second.actor4_name == actor ||
					arr[i][j].second.actor5_name == actor) {
					Print(arr[i][j].second);
					printed = true;
				}
			}
		}

		if (!printed) {
			cout << "There are no documented movies with that actor." << endl;
		}
	}

	//used for testing
	void PrintAll() {
		for (int i = 0; i < capacity; i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				Print(arr[i][j].second);
			}
		}
	}

};

struct RBTree {
	Movie* root;
	void rotateLeft(Movie* node1, Movie* node2);
	void rotateRight(Movie* node1, Movie* node2);
	void inorder(Movie* newNode);
	void fixColor(Movie* node1, Movie* node2);
	RBTree() {
		root = NULL;
	}
	void insert(Movie* newNode);
	Movie* BSTInsert(Movie* root, Movie* newNode);
	void searchMovieTitle(string title, Movie* root);
	void searchMovieActor(string actor, string genre, Movie* root, Movie* stableRoot);
	void searchGenre(string genre, Movie* root, Movie* stableRoot);
	void levelOrderTitleSearch(string title, Movie* root);
};

Movie::Movie()
{
	genres = "";
	popularity = 0;
	revenue = "";
	runtime = 0;
	actor1_name = "";
	actor2_name = "";
	actor3_name = "";
	actor4_name = "";
	actor5_name = "";
	director_name = "";
	producer_name = "";
	screenplay_writer_name = "";
	editor_name = "";
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	color = RED;
}

Movie::Movie(string _genres, float _popularity, string _revenue, int _runtime, string _title, string actor1, string actor2, string actor3, string actor4, string actor5, string director, string producer, string screenplay, string editor)
{
	genres = _genres;
	popularity = _popularity;
	revenue = _revenue;
	runtime = _runtime;
	title = _title;
	actor1_name = actor1;
	actor2_name = actor2;
	actor3_name = actor3;
	actor4_name = actor4;
	actor5_name = actor5;
	director_name = director;
	producer_name = producer;
	screenplay_writer_name = screenplay;
	editor_name = editor;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	color = RED;
}

void Movie::operator=(Movie* next)
{
	genres = next->genres;
	popularity = next->popularity;
	revenue = next->revenue;
	runtime = next->runtime;
	title = next->title;
	actor1_name = next->actor1_name;
	actor2_name = next->actor2_name;
	actor3_name = next->actor3_name;
	actor4_name = next->actor4_name;
	actor5_name = next->actor5_name;
	director_name = next->director_name;
	producer_name = next->producer_name;
	screenplay_writer_name = next->screenplay_writer_name;
	editor_name = next->editor_name;
}

void Movie::PrintMovie()
{
	cout << "Genres: " << genres << endl;
	cout << "Popularity: " << popularity << endl;
	cout << "Revenue: " << revenue << endl;
	cout << "Runtime: " << runtime << endl;
	cout << "Title: " << title << endl;
	cout << "Actor 1: " << actor1_name << endl;
	cout << "Actor 2: " << actor2_name << endl;
	cout << "Actor 3: " << actor3_name << endl;
	cout << "Actor 4: " << actor4_name << endl;
	cout << "Actor 5: " << actor5_name << endl;
	cout << "Director: " << director_name << endl;
	cout << "Producer: " << producer_name << endl;
	cout << "Screenplay by: " << screenplay_writer_name << endl;
	cout << "Editor: " << editor_name << endl;
}

void Movie::setGenres(string _genres) {
	genres = _genres;
}
void Movie::setPop(string _pop) {
	this->popularity = stof(_pop);
}
void Movie::setRevenue(string _revenue) {
	this->revenue = _revenue;
}
void Movie::setRuntime(string _runtime) {
	this->runtime = stoi(_runtime);
}
void Movie::setTitle(string _title) {
	this->title = _title;
}
void Movie::setActor1(string _actor1) {
	this->actor1_name = _actor1;
}
void Movie::setActor2(string _actor2) {
	this->actor2_name = _actor2;
}
void Movie::setActor3(string _actor3) {
	this->actor3_name = _actor3;
}
void Movie::setActor4(string _actor4) {
	this->actor4_name = _actor4;
}
void Movie::setActor5(string _actor5) {
	this->actor5_name = _actor5;
}
void Movie::setDirector(string _director) {
	this->director_name = _director;
}
void Movie::setProducer(string _producer) {
	this->producer_name = _producer;
}
void Movie::setScreenplay(string _screenplay) {
	this->screenplay_writer_name = _screenplay;
}
void Movie::setEditor(string _editor) {
	this->editor_name = _editor;
}

void RBTree::rotateLeft(Movie* root, Movie* newNode) {
	Movie* rightPT = newNode->right;
	newNode->right = rightPT->left;
	if (newNode->right != NULL) {
		newNode->right->parent = newNode;
	}
	rightPT->parent = newNode->parent;
	if (newNode->parent == NULL) {
		root = rightPT;
	}
	else if (newNode == newNode->parent->left) {
		newNode->parent->left = rightPT;
	}
	else {
		newNode->parent->right = rightPT;
	}
	rightPT->left = newNode;
	newNode->parent = rightPT;
}
void RBTree::rotateRight(Movie* root, Movie* newNode) {
	Movie* leftPT = newNode->left;
	newNode->left = leftPT->right;
	if (newNode->left != NULL) {
		newNode->left->parent = newNode;
	}
	leftPT->parent = newNode->parent;
	if (newNode->parent == NULL) {
		root = leftPT;
	}
	else if (newNode == newNode->parent->left) {
		newNode->parent->left = leftPT;
	}
	else {
		newNode->parent->left = leftPT;
	}
	leftPT->right = newNode;
	newNode->parent = leftPT;
}
void RBTree::fixColor(Movie* root, Movie* newNode) {
	Movie* parentPointer = nullptr;
	Movie* grandParentPointer = nullptr;
	//changing this to red
	while ((newNode != root) && (newNode->color != RED) && (newNode->parent->color == RED)) {
		parentPointer = newNode->parent;
		grandParentPointer = parentPointer->parent;

		//if parent of pointer is left child of grandparent pointer
		if (parentPointer == grandParentPointer->left) {
			Movie* unclePointer = grandParentPointer->right;
			//if the uncle pointer is also red only recoloring required
			if (unclePointer != nullptr && unclePointer->color == RED) {
				grandParentPointer->color = RED;
				parentPointer->color = BLACK;
				unclePointer->color = BLACK;
				newNode = grandParentPointer;
			}
			//if newNode is right child of its parent left rotation is required
			else {
				if (newNode == parentPointer->right) {
					rotateLeft(root, parentPointer);
					newNode = parentPointer;
					parentPointer = newNode->parent;
				}
				rotateRight(root, grandParentPointer);
				swap(parentPointer->color, grandParentPointer->color);
				newNode = parentPointer;
			}
		}
		//if parent of newNode is the right child of grandparent pointer
		else {
			Movie* unclePT = grandParentPointer->left;
			//if the uncle of the newNode is also red only recoloring required
			if ((unclePT != nullptr) && (unclePT->color == RED)) {
				grandParentPointer->color = RED;
				parentPointer->color = BLACK;
				unclePT->color = BLACK;
				newNode = grandParentPointer;
			}
			else {
				//newNode is left child of its parent right rotation required
				if (newNode == parentPointer->left) {
					rotateRight(root, parentPointer);
					newNode = parentPointer;
					parentPointer = newNode->parent;
				}
				rotateLeft(root, grandParentPointer);
				swap(parentPointer->color, grandParentPointer->color);
				newNode = parentPointer;
			}
		}
	}
	root->color = BLACK;

}
Movie* RBTree::BSTInsert(Movie* root, Movie* newNode) {
	if (root == nullptr) { //if tree is empty return new node
		return newNode;
	}
	if (newNode->title[0] < root->title[0]) {
		root->left = BSTInsert(root->left, newNode);
		root->left->parent = root;
	}
	else {// if (newNode->title[0] > root->title[0]) {
		root->right = BSTInsert(root->right, newNode);
		root->right->parent = root;
	}
	return root;
}
void RBTree::insert(Movie* newNode) {
	root = BSTInsert(root, newNode);
	//cout << newNode->title << endl;
	fixColor(root, newNode);
}
void RBTree::inorder(Movie* newNode) {
	if (newNode == nullptr)
		return;

	inorder(newNode->left);
	cout << newNode->title << ", ";
	inorder(newNode->right);
}
void RBTree::searchMovieTitle(string title, Movie* root) {
	if (root == nullptr) {
		return;
	}
	//inorder(root);
	//searchMovieTitle(title, root->left);
	//cout << root->title << endl;
	if (root->title == title) {
		cout << "Found: " << root->title << endl;
		cout << "Genres: " << root->genres << endl;
		cout << "Popularity: " << root->popularity << endl;
		cout << "Revenue: " << root->revenue << endl;
		cout << "Runtime: " << root->runtime << endl;
		cout << "Title: " << root->title << endl;
		cout << "Actor 1: " << root->actor1_name << endl;
		cout << "Actor 2: " << root->actor2_name << endl;
		cout << "Actor 3: " << root->actor3_name << endl;
		cout << "Actor 4: " << root->actor4_name << endl;
		cout << "Actor 5: " << root->actor5_name << endl;
		cout << "Director: " << root->director_name << endl;
		cout << "Producer: " << root->producer_name << endl;
		cout << "Screenplay by: " << root->screenplay_writer_name << endl;
		cout << "Editor: " << root->editor_name << endl;
	}

	if (title[0] < root->title[0]) {
		searchMovieTitle(title, root->left);
	}
	else {
		searchMovieTitle(title, root->right);
	}

	/*
	vector<Movie*> vecToPrint;
	stack<Movie*> stack;
	Movie* curr=root;
	while(!stack.empty() || curr!=nullptr){
		if(curr!= nullptr){
			stack.push(curr);
			curr=curr->left;
		}
		else{
			curr=stack.top();
			stack.pop();
			if(title==curr->title) {
				vecToPrint.push_back(curr);
			}
			curr=curr->right;
		}
	}
	if (!vecToPrint.empty()) {
		sort(vecToPrint.begin(), vecToPrint.end());
		for (int i = 0; i < vecToPrint.size(); i++) {
			//vecToPrint[i]->PrintMovie();
			cout << "Genres: " << vecToPrint[i]->genres << endl;
			cout << "Popularity: " << vecToPrint[i]->popularity << endl;
			cout << "Revenue: " << vecToPrint[i]->revenue << endl;
			cout << "Runtime: " << vecToPrint[i]->runtime << endl;
			cout << "Title: " << vecToPrint[i]->title << endl;
			cout << "Actor 1: " << vecToPrint[i]->actor1_name << endl;
			cout << "Actor 2: " << vecToPrint[i]->actor2_name << endl;
			cout << "Actor 3: " << vecToPrint[i]->actor3_name << endl;
			cout << "Actor 4: " << vecToPrint[i]->actor4_name << endl;
			cout << "Actor 5: " << vecToPrint[i]->actor5_name << endl;
			cout << "Director: " << vecToPrint[i]->director_name << endl;
			cout << "Producer: " << vecToPrint[i]->producer_name << endl;
			cout << "Screenplay by: " << vecToPrint[i]->screenplay_writer_name << endl;
			cout << "Editor: " << vecToPrint[i]->editor_name << endl;
		}
	}
	else {
		cout << "There are no documented movies with that title." << endl;
	}
	 */
}

void RBTree::levelOrderTitleSearch(string title, Movie* root) {
	if (root == nullptr) {
		return;
	}
	cout << "THIS IS " << title << endl;
	queue<Movie*> q;
	q.push(root);
	while (q.empty() == false) {
		int nodeCount = q.size();
		while (nodeCount > 0) {
			Movie* node = q.front();
			if (node->title == title) {
				cout << "Found: " << node->title << endl;
				cout << "Genres: " << node->genres << endl;
				cout << "Popularity: " << node->popularity << endl;
				cout << "Revenue: " << node->revenue << endl;
				cout << "Runtime: " << node->runtime << endl;
				cout << "Title: " << node->title << endl;
				cout << "Actor 1: " << node->actor1_name << endl;
				cout << "Actor 2: " << node->actor2_name << endl;
				cout << "Actor 3: " << node->actor3_name << endl;
				cout << "Actor 4: " << node->actor4_name << endl;
				cout << "Actor 5: " << node->actor5_name << endl;
				cout << "Director: " << node->director_name << endl;
				cout << "Producer: " << node->producer_name << endl;
				cout << "Screenplay by: " << node->screenplay_writer_name << endl;
				cout << "Editor: " << node->editor_name << endl;
			}
			q.pop();
			if (node->left != nullptr) {
				q.push(node->left);
			}
			if (node->right != nullptr) {
				q.push(node->right);
			}
			nodeCount--;
		}
	}
}

void RBTree::searchMovieActor(string actor, string genre, Movie* root, Movie* stableRoot) {
	if (root == nullptr) {
		return;
	}
	//cout << root->title << endl;

	if (root->genres.find(genre) != string::npos && (actor == root->actor1_name || actor == root->actor2_name || actor == root->actor3_name || actor == root->actor4_name || actor == root->actor5_name)) {
		/*cout << "Genres: " << root->genres << endl;
		cout << "Popularity: " << root->popularity << endl;
		cout << "Revenue: " << root->revenue << endl;
		cout << "Runtime: " << root->runtime << endl;*/
		cout << "Title: " << root->title << endl;
		/*cout << "Actor 1: " << root->actor1_name << endl;
		cout << "Actor 2: " << root->actor2_name << endl;
		cout << "Actor 3: " << root->actor3_name << endl;
		cout << "Actor 4: " << root->actor4_name << endl;
		cout << "Actor 5: " << root->actor5_name << endl;
		cout << "Director: " << root->director_name << endl;
		cout << "Producer: " << root->producer_name << endl;
		cout << "Screenplay by: " << root->screenplay_writer_name << endl;
		cout << "Editor: " << root->editor_name << endl;*/
	}
	searchMovieActor(actor, genre, root->left, root);
	searchMovieActor(actor, genre, root->right, root);


	/*
	vector<Movie*> vecToPrint;
	stack<Movie*> stack;
	Movie* curr=root;
	while(!stack.empty() || curr!=nullptr){
		if(curr!=nullptr){
			stack.push(curr);
			curr=curr->left;
		}
		else{
			curr=stack.top();
			stack.pop();
			if (actor == root->actor1_name || actor == root->actor2_name || actor == root->actor3_name || actor == root->actor4_name || actor == root->actor5_name) {
				vecToPrint.push_back(curr);
			}
			curr=curr->right;
		}
	}
	if (!vecToPrint.empty()) {
		sort(vecToPrint.begin(), vecToPrint.end());
		for (int i = 0; i < vecToPrint.size(); i++) {
			//vecToPrint[i]->PrintMovie();
			cout << "Genres: " << vecToPrint[i]->genres << endl;
			cout << "Popularity: " << vecToPrint[i]->popularity << endl;
			cout << "Revenue: " << vecToPrint[i]->revenue << endl;
			cout << "Runtime: " << vecToPrint[i]->runtime << endl;
			cout << "Title: " << vecToPrint[i]->title << endl;
			cout << "Actor 1: " << vecToPrint[i]->actor1_name << endl;
			cout << "Actor 2: " << vecToPrint[i]->actor2_name << endl;
			cout << "Actor 3: " << vecToPrint[i]->actor3_name << endl;
			cout << "Actor 4: " << vecToPrint[i]->actor4_name << endl;
			cout << "Actor 5: " << vecToPrint[i]->actor5_name << endl;
			cout << "Director: " << vecToPrint[i]->director_name << endl;
			cout << "Producer: " << vecToPrint[i]->producer_name << endl;
			cout << "Screenplay by: " << vecToPrint[i]->screenplay_writer_name << endl;
			cout << "Editor: " << vecToPrint[i]->editor_name << endl;
		}
	}
	else {
		cout << "There are no documented movies with that actor." << endl;
	}
	 */
}
void RBTree::searchGenre(string genre, Movie* root, Movie* stableRoot) {
	if (root == nullptr) {
		return;
	}
	if (root->genres.find(genre) != string::npos) {
		/*cout << "Genres: " << root->genres << endl;
		cout << "Popularity: " << root->popularity << endl;
		cout << "Revenue: " << root->revenue << endl;
		cout << "Runtime: " << root->runtime << endl;*/
		cout << "Title: " << root->title << endl;
		/*cout << "Actor 1: " << root->actor1_name << endl;
		cout << "Actor 2: " << root->actor2_name << endl;
		cout << "Actor 3: " << root->actor3_name << endl;
		cout << "Actor 4: " << root->actor4_name << endl;
		cout << "Actor 5: " << root->actor5_name << endl;
		cout << "Director: " << root->director_name << endl;
		cout << "Producer: " << root->producer_name << endl;
		cout << "Screenplay by: " << root->screenplay_writer_name << endl;
		cout << "Editor: " << root->editor_name << endl;*/
	}

	searchGenre(genre, root->left, root);
	searchGenre(genre, root->right, root);


	/*
	vector<Movie*> vecToPrint;
	stack<Movie*> stack;
	Movie* curr=root;
	while(!stack.empty() || curr!=nullptr){
		if(curr!=nullptr){
			stack.push(curr);
			curr=curr->left;
		}
		else{
			curr=stack.top();
			stack.pop();
			if (genre == root->genres) {
				vecToPrint.push_back(root);
			}
			curr=curr->right;
		}
	}
	if (!vecToPrint.empty()) {
		sort(vecToPrint.begin(), vecToPrint.end());
		for (int i = 0; i < vecToPrint.size(); i++) {
			//vecToPrint[i]->PrintMovie();
			cout << "Genres: " << vecToPrint[i]->genres << endl;
			cout << "Popularity: " << vecToPrint[i]->popularity << endl;
			cout << "Revenue: " << vecToPrint[i]->revenue << endl;
			cout << "Runtime: " << vecToPrint[i]->runtime << endl;
			cout << "Title: " << vecToPrint[i]->title << endl;
			cout << "Actor 1: " << vecToPrint[i]->actor1_name << endl;
			cout << "Actor 2: " << vecToPrint[i]->actor2_name << endl;
			cout << "Actor 3: " << vecToPrint[i]->actor3_name << endl;
			cout << "Actor 4: " << vecToPrint[i]->actor4_name << endl;
			cout << "Actor 5: " << vecToPrint[i]->actor5_name << endl;
			cout << "Director: " << vecToPrint[i]->director_name << endl;
			cout << "Producer: " << vecToPrint[i]->producer_name << endl;
			cout << "Screenplay by: " << vecToPrint[i]->screenplay_writer_name << endl;
			cout << "Editor: " << vecToPrint[i]->editor_name << endl;
		}
	}
	else {
		cout << "There are no documented movies with that genre." << endl;
	}
	 */
}

void readCSV(RBTree* tree, HashTable hash);

int main()
{
	HashTable hash(300000);
	RBTree tree;
	RBTree* treePoint = &tree;
	readCSV(treePoint, hash);
	treePoint->root->PrintMovie();

	string input = "";
	while (input != "-1") {
		string movieTitle = "";
		string movieActor = "";
		string movieGenre = "";
		Movie userInput;
		input = "-2";
		while (input != "-1" && input != "1" && input != "2" && input != "3") {
			cout << "Search by Movie (1), actor (2), or genre(3). Exit with -1 \n";
			cin >> input;
		}
		if (stoi(input) == 1) {
			cout << "Insert Movie Title: ";
			cin.ignore();
			getline(cin, movieTitle);
			// search
			chrono::steady_clock::time_point start = chrono::steady_clock::now();
			treePoint->searchMovieTitle(movieTitle, treePoint->root);
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

			cout << endl << "//// LEVEL ORDER //// " << movieTitle << endl;
			chrono::steady_clock::time_point start2 = chrono::steady_clock::now();
			treePoint->levelOrderTitleSearch(movieTitle, treePoint->root);
			chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
			cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << endl << endl;
		}
		else if (stoi(input) == 2) {
			cout << "Insert an actor: ";
			cin.ignore();
			getline(cin, movieActor);
			cout << "Insert a genre: ";
			cin.ignore();
			getline(cin, movieGenre);
			// search
			chrono::steady_clock::time_point start = chrono::steady_clock::now();
			treePoint->searchMovieActor(movieActor, movieGenre, treePoint->root, treePoint->root);
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;
		}
		else if (stoi(input) == 3) {
			cout << "Insert a genre: ";
			cin.ignore();
			getline(cin, movieGenre);
			// search
			chrono::steady_clock::time_point start = chrono::steady_clock::now();
			treePoint->searchGenre(movieGenre, treePoint->root, treePoint->root);
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			cout << "Microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;
		}
	}
}
void readCSV(RBTree* tree, HashTable hash)
{
	fstream inClean("AllMoviesDetailsCleaned.csv");
	fstream inRaw("AllMoviesCastingRaw.csv");
	int count = 0; // keeps track of how many movies added.
	int temp = 0; // keeps track of how many lines traversed.
	string line; // used to set detailsCleaned values
	string item; // used to set castingRaw values
	getline(inClean, line);
	getline(inRaw, line);
	int diff = 0;

	if (inClean.is_open() && inRaw.is_open()) {
		// can lower conditional when testing so the entire file doesn't need to be run every time. Takes appprox 2mins 10s without adding to data structure
		while (temp < 10000) { //328842 is max, error after 198152-> correlates to id: 314304
			Movie* node = new Movie();
			Movie movie = Movie();

			string _idC = "";
			string _genres = "";
			string _popularity = ".1"; // float
			string _revenue = ""; // string because of overflow possibility
			string _runtime = "1"; // int
			string _title = "";
			string _idR = "";
			string _actor1_name = "";
			string _actor2_name = "";
			string _actor3_name = "";
			string _actor4_name = "";
			string _actor5_name = "";
			string _director_name = "";
			string _producer_name = "";
			string _screenplay_writer_name = "";
			string _editor_name = "";

			if (getline(inClean, line)) { // gets data from detailsCleaned.csv

				istringstream stream(line);
				// runs through each column, but only collects some
				getline(stream, _idC, ';');
				getline(stream, item, ';'); // item is used as a placeholder for values not collected
				getline(stream, _genres, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, _popularity, ';');
				while (!isFloat(_popularity)) { // in some cases there is a ; not as a delimiter.
												//This checks to see if the next value is a float as it should be instead of a string continued from the previous column
					getline(stream, _popularity, ';');
				}
				if (_popularity == "")
					_popularity = "0.0";
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, _revenue, ';');
				if (_revenue == "")
					_revenue = "0"; // can cause problems otherwise when converting to an int
				getline(stream, _runtime, ';');
				if (_runtime == "")
					_runtime = "0";
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, _title, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');
				getline(stream, item, ';');

			}

			if (getline(inRaw, item)) { // gets data from castingRaw.csv
				istringstream stream2(item);

				getline(stream2, _idR, ';');
				getline(stream2, _actor1_name, ';');
				getline(stream2, line, ';');
				getline(stream2, _actor2_name, ';');
				getline(stream2, line, ';');
				getline(stream2, _actor3_name, ';');
				getline(stream2, line, ';');
				getline(stream2, _actor4_name, ';');
				getline(stream2, line, ';');
				getline(stream2, _actor5_name, ';');
				getline(stream2, line, ';');
				getline(stream2, line, ';');
				getline(stream2, _director_name, ';');
				getline(stream2, line, ';');
				getline(stream2, line, ';');
				getline(stream2, _producer_name, ';');
				getline(stream2, line, ';');
				getline(stream2, _screenplay_writer_name, ';');
				getline(stream2, _editor_name, ';');

			}
			temp++;

			if (_idC != _idR) // should not occur. If IDs of the movies do not match then the data from both csv files will also not match
				cout << "Clean: " << _idC << "Raw: " << _idR << endl;

			// = Movie(_genres, stof(_popularity), _revenue, stoi(_runtime), _title, _actor1_name, _actor2_name, _actor3_name, _actor4_name, _actor5_name, _director_name, _producer_name, _screenplay_writer_name, _editor_name);


			if (isAlph(_title) && temp != 198152 && _genres != "" && _actor1_name != "" && _title != "") { // bad data at 198152
				node->setGenres(_genres);
				node->setPop(_popularity);
				node->setRevenue(_revenue);
				node->setRuntime(_runtime);
				node->setTitle(_title);
				node->setActor1(_actor1_name);
				node->setActor2(_actor2_name);
				node->setActor3(_actor3_name);
				node->setActor4(_actor4_name);
				node->setActor5(_actor5_name);
				node->setDirector(_director_name);
				node->setProducer(_producer_name);
				node->setScreenplay(_screenplay_writer_name);
				node->setEditor(_editor_name);


				movie.setGenres(_genres);
				movie.setPop(_popularity);
				movie.setRevenue(_revenue);
				movie.setRuntime(_runtime);
				movie.setTitle(_title);
				movie.setActor1(_actor1_name);
				movie.setActor2(_actor2_name);
				movie.setActor3(_actor3_name);
				movie.setActor4(_actor4_name);
				movie.setActor5(_actor5_name);
				movie.setDirector(_director_name);
				movie.setProducer(_producer_name);
				movie.setScreenplay(_screenplay_writer_name);
				movie.setEditor(_editor_name);

				//cout << temp << endl;
				//hash.Insert(movie);
				//node.PrintMovie();
				// Add to tree.

				tree->insert(node);

				//node->PrintMovie();
				//if (_title == "Tron")
					//node->PrintMovie();
				count++;
				//cout << count << endl;
			}
			//else
				//cout << "not letter " << _title << " " << _idC << endl;

		}
	}
	//tree->root->PrintMovie();
	cout << endl;
}

bool isFloat(string str)
{
	for (int i = 0; i < str.length(); i++) { // the non-numerical values occur if popularity is very close to 0. ex: 7.5E-5
		if ((str[i] != '.') && (str[i] != 'E') && (str[i] != 'e') && (str[i] != ',') && (str[i] != '-') && (str[i] != '0' && str[i] != '1'
			&& str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9')) {
			return false; //|to do| if 'E', 'e', ',', or '-' then set to 0.0 as well
		}

	}
	return true;
}

bool isAlph(string str) // isaplha() function gives error on different language scripts, so a personalized function is needed to remove them.
{
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != 'A' && str[i] != 'a' && str[i] != 'B' && str[i] != 'b' && str[i] != 'C' && str[i] != 'c' && str[i] != 'D' && str[i] != 'd'
			&& str[i] != 'E' && str[i] != 'e' && str[i] != 'F' && str[i] != 'f' && str[i] != 'G' && str[i] != 'g' && str[i] != 'H' && str[i] != 'h'
			&& str[i] != 'I' && str[i] != 'i' && str[i] != 'J' && str[i] != 'j' && str[i] != 'K' && str[i] != 'k' && str[i] != 'L' && str[i] != 'l'
			&& str[i] != 'M' && str[i] != 'm' && str[i] != 'N' && str[i] != 'n' && str[i] != 'O' && str[i] != 'o' && str[i] != 'P' && str[i] != 'p'
			&& str[i] != 'Q' && str[i] != 'q' && str[i] != 'R' && str[i] != 'r' && str[i] != 'S' && str[i] != 's' && str[i] != 'T' && str[i] != 't'
			&& str[i] != 'U' && str[i] != 'u' && str[i] != 'V' && str[i] != 'v' && str[i] != 'W' && str[i] != 'w' && str[i] != 'X' && str[i] != 'x'
			&& str[i] != 'Y' && str[i] != 'y' && str[i] != 'Z' && str[i] != 'z' && str[i] != ' ' && str[i] != ':' && str[i] != ',' && str[i] != '.'
			&& str[i] != '\'' && str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6'
			&& str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '!' && str[i] != '(' && str[i] != ')' && str[i] != '-' && str[i] != '&'
			&& str[i] != '?' && str[i] != '/' && str[i] != '"') {
			return false;
		}

	}
	return true;
}
