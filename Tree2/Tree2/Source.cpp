//#include<SFML\Graphics.hpp>
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<math.h>
#include<SFML/Graphics.hpp>
struct node
{
	node* left;
	node* right;
	
	sf::Text text;
	sf::Font font;
	int data;
	sf::CircleShape circ;
	
};
node* root = NULL;
void updateOrigin(node*);

void display(sf::RenderWindow*);
void delay(int x);
void draw(sf::RenderWindow* window, node* temp);
void Options(sf::RenderWindow* window);
int retlen(int value)
{
	int a=0;
	while (value > 0)
	{
		value = value / 10;
		a++;
	}
	return a;
}
node* newNode(int key)
{
	
	std::string ch = std::to_string(key);
	std::cout << "string value  " << ch << std::endl;
	node* newnode = new node;
	newnode->font.loadFromFile("times.ttf");
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = key;
	newnode->circ.setRadius(30);
	newnode->circ.setFillColor(sf::Color::Blue);
	newnode->circ.setOutlineThickness(10);
	newnode->circ.setOutlineColor(sf::Color::White);
	newnode->text.setFont(newnode->font);
	newnode->text.setString(ch);
	newnode->text.setCharacterSize(45 - retlen(key) * 5);
	newnode->text.setOrigin(sf::Vector2f(0, 0));
	
	return newnode;

}

node* retParent(node* Root, node* temp)
{
	node* parent = NULL;
	node* t = Root;

	while (t != temp)
	{
		parent = t;
		if (temp->data < t->data)
		{
			t = t->left;
		}
		else t = t->right;
	}
	return parent;

}
void insert(sf::RenderWindow* window,int key)
{
	node* newnode = newNode(key);
	node* temp = root;
	node* parent = root;
	if (root == NULL)
	{
		root = newnode;
		updateOrigin(root);
		window->clear(sf::Color::Black);
		draw(window, root);
		display(window);
		return;
	}
	else
	{
		temp = root;
		while (temp != NULL)
		{
			if (temp->data < key)
			{
				parent = temp;
				temp = temp->right;
			}
			else if (temp->data > key)
			{
				parent = temp;
				temp = temp->left;
			}
		}
		if (parent->data < key)
		{
			parent->right = newnode;
		}
		else
		{
			parent->left = newnode;
		}
	}
	updateOrigin(root);
	window->clear(sf::Color::Black);
	draw(window,root);
	display(window);
}
sf::Vector2f retParentPos(node* temp)
{
	return retParent(root, temp)->circ.getPosition();
}
void updateOrigin(node* temp)
{
	static int i=0;
	if (temp != NULL)
	{
		if (retParent(root, temp) != NULL)
		{
			if (retParent(root, temp)->data > temp->data) {
				temp->circ.setPosition(sf::Vector2f(retParent(root, temp)->circ.getPosition().x - (300/powf(2,i)), retParent(root, temp)->circ.getPosition().y + 150));
				
			}
			else
				temp->circ.setPosition(sf::Vector2f(retParent(root, temp)->circ.getPosition().x + (300 / powf(2, i)), retParent(root, temp)->circ.getPosition().y + 150));
			
		}
		else
			temp->circ.setPosition(sf::Vector2f(600, 40));//position of root
		i++;
		temp->text.setPosition(sf::Vector2f(temp->circ.getPosition().x+10, temp->circ.getPosition().y+10));
		updateOrigin(temp->left);
		updateOrigin(temp->right);
		i = 0;
	}
}
void inorder(sf::RenderWindow* window,node* temp)
{
	if (temp != NULL)
	{
		
		temp->circ.setFillColor(sf::Color::White);
		draw(window, root);
		display(window);
		temp->circ.setFillColor(sf::Color::Blue);
		inorder(window, temp->left);
		inorder(window, temp->right);
	}
}
float todegree(float x)
{
	return (x*57.29);
}
void draw(sf::RenderWindow* window,node* temp)
{
	float angle;
	sf::RectangleShape Rectro;
	
	static int i = 0;
		if (temp != NULL)
		{
			
			if(temp->left==NULL && temp->right==NULL && temp!=root)
				temp->circ.setFillColor(sf::Color::Red);
			else if (temp == root)
				temp->circ.setFillColor(sf::Color::Green);
			else temp->circ.setFillColor(sf::Color::Blue);
			
			Rectro.setPosition(sf::Vector2f(temp->circ.getPosition().x+30, temp->circ.getPosition().y + 25));
			
			Rectro.setSize(sf::Vector2f(346/powf(2,i), 5));
			angle = atan(2 / powf(2, i));
			angle = todegree(angle);
			Rectro.setRotation(90-angle);
			if(temp->right!=NULL)
			window->draw(Rectro);
			Rectro.setRotation(90+angle);
			if(temp->left!=NULL)
			window->draw(Rectro);
			window->draw(temp->circ);
			window->draw(temp->text);
			i++;
			draw(window, temp->left);
			
			draw(window, temp->right);
			i = 0;
		}
		
	
}
void display(sf::RenderWindow* window)
{
	
	window->display();
	delay(2000);
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{

	}
}
void delay(int x)
{
	sf::Clock clock;
	sf::Time time;
	clock.restart();

	while (time.asMilliseconds() < x)
	{
		time = clock.getElapsedTime();

	}
}
node* minimum(node* temp)
{
	if (temp == NULL)
	{
		return NULL;
	}
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}
void deletion(sf::RenderWindow* window,node* temp, int key)
{
	node* head = temp;
	node* parent = NULL;
	if (temp == NULL) {
		std::cout << "void deletion" << std::endl;
		return;
	}
	while (1)
	{
		if (key < temp->data)//element must be at the left
		{

			parent = temp;
			temp = temp->left;
		}
		else if (key > temp->data)//element is at the right
		{

			parent = temp;
			temp = temp->right;
		}
		else if (key == temp->data)
		{
			if (temp->left == NULL && temp->right == NULL)
			{

				if (parent->data > temp->data)
					parent->left = NULL;
				else parent->right = NULL;
				
				break;
			}
			else if (temp->left == NULL)
			{
				if (temp->data > retParent(head, temp)->data)
					(retParent(head, temp))->right = temp->right;
				else
					(retParent(head, temp))->left = temp->right;
				break;
			}
			else if (temp->right == NULL)
			{

				if (temp->data > retParent(head, temp)->data)
					(retParent(head, temp))->right = temp->left;
				else
					(retParent(head, temp))->left = temp->left;
				break;
			}

			else
			{
				if (minimum(temp->right) != NULL) {
					temp->data = minimum(temp->right)->data;
					(retParent(head, minimum(temp->right)))->left = NULL;
				}

				break;
			}
		}
		else
		{
			std::cout << "element not found " << std::endl;
			break;
		}
	}
	updateOrigin(root);
	window->clear(sf::Color::Black);
	draw(window, root);
	display(window);
	return;
}
void keypad(sf::RenderWindow* window,int x)
{
	int position, data;
	sf::Text head;
	sf::Text inputtext[20];
	sf::RectangleShape cursor;
	cursor.setSize(sf::Vector2f(3.0f, 40.0f));
	cursor.setOrigin(sf::Vector2f(0, 0));
	cursor.setPosition(sf::Vector2f(210, 310));
	cursor.setFillColor(sf::Color::Black);
	int i;
	int j;

	sf::RectangleShape rect[4][3], rectBig;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 3; i++)
		{
			rect[j][i].setSize(sf::Vector2f(100, 100));
			rect[j][i].setOrigin(sf::Vector2f(0, 0));
			rect[j][i].setPosition(sf::Vector2f(200 + 100 * i, 400 + j * 100));
			rect[j][i].setFillColor(sf::Color::Magenta);
			rect[j][i].setOutlineThickness(10.0f);

			rect[j][i].setOutlineColor(sf::Color::Black);
		}
	}
	rectBig.setSize(sf::Vector2f(300, 500));
	rectBig.setOrigin(sf::Vector2f(0, 0));
	rectBig.setPosition(sf::Vector2f(200, 270));
	rectBig.setOutlineThickness(10.0f);
	rectBig.setOutlineColor(sf::Color::Green);
	sf::Font font;
	font.loadFromFile("times.ttf");
	 {
		head.setFont(font);
		head.setPosition(sf::Vector2f(190, 180));
		head.setCharacterSize(60);
		head.setFillColor(sf::Color::Blue);
	}
	
	head.setString(">>Insert the data ");
	for (i = 0; i < 20; i++)
	{
		inputtext[i].setFont(font);
		inputtext[i].setPosition(sf::Vector2f(205, 300));
		inputtext[i].setCharacterSize(50);
		inputtext[i].setFillColor(sf::Color::Black);
	}
	
	sf::Text text[4][3];
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 3; i++)
		{
			text[j][i].setFont(font);
			text[j][i].setPosition(sf::Vector2f(225 + 100 * i, 400 + j * 100));
			text[j][i].setCharacterSize(70);
			text[j][i].setFillColor(sf::Color::Yellow);
		}
	}
	text[0][0].setString('1');
	text[0][1].setString("2");
	text[0][2].setString("3");
	text[1][0].setString("4");
	text[1][1].setString("5");
	text[1][2].setString("6");
	text[2][0].setString("7");
	text[2][1].setString("8");
	text[2][2].setString("9");
	text[3][0].setString("Clear");
	text[3][1].setString("0");
	text[3][2].setString("OK");
	text[3][0].setCharacterSize(35);
	text[3][0].setPosition(sf::Vector2f(205 + 100 * 0, 430 + 3 * 100));
	text[3][2].setCharacterSize(40);
	text[3][2].setPosition(sf::Vector2f(210 + 100 * 2, 430 + 3 * 100));
	int k = 1;
	sf::Clock clock;
	sf::Time t;
	clock.restart();
	int l = 0;

	int number = 0;

	int numberValue = 0;
	while (window->isOpen())
	{

		window->clear(sf::Color::Black);
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		
			window->draw(head);
		window->draw(rectBig);
		for (i = 0; i < 20; i++) {
			window->draw(inputtext[i]);
		}
		t = clock.getElapsedTime();
		if (k == 1)
		{
			window->draw(cursor);
			if (t.asMilliseconds() > 500)
				k = 0;
		}
		{

			if (t.asMilliseconds() > 1000)
			{
				k = 1;
				clock.restart();
			}


		}
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				window->draw(rect[i][j]);
				window->draw(text[i][j]);
			}
		}

		window->display();
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (abs(mousePos.x) > rect[i][j].getPosition().x && abs(mousePos.x) < (rect[i][j].getPosition().x + rect[i][j].getSize().x) && abs(mousePos.y) > (rect[i][j].getPosition().y + 40) && abs(mousePos.y) < (rect[i][j].getPosition().y + rect[0][0].getSize().y + 40))
				{
					rect[i][j].setFillColor(sf::Color::White);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (!((i == 3 && j == 2) || (i == 3 && j == 0))) {
							inputtext[l].setString(text[i][j].getString());
							inputtext[l].setPosition(cursor.getPosition().x - 10, cursor.getPosition().y);
							cursor.move(sf::Vector2f(25, 0));
							l++;
						}

						//Backspace
						if (i == 3 && j == 0)
						{
							cursor.move(sf::Vector2f(-25, 0));
							if (cursor.getPosition().x < 210)
								cursor.setPosition(sf::Vector2f(210, 310));

							else l--;


						}
						inputtext[l].setString("");
						std::string  ch[20];
						int T = l;
						//ok
						if (i == 3 && j == 2)
						{
							int f = 0;
							while (inputtext[f].getString() != "")
							{
								ch[f] = inputtext[f].getString();

								std::stringstream(ch[f]) >> numberValue;
								number += numberValue * powf(10, T - f - 1);
								f++;
							}
							
							
								data = number;

							f = 0;
							while (inputtext[f].getString() != "")
							{
								inputtext[f].setString("");
								f++;

							}
							
							cursor.setPosition(sf::Vector2f(210, 310));
							l = 0;
							if(x==0)
							{
								delay(200);
								insert(window, data);
								return;
							}
							
							else
							{
								delay(200);
								deletion(window, root,data);
								return;
							}
							//number = 0;
							
						}
						delay(200);
					}
				}
				else rect[i][j].setFillColor(sf::Color::Magenta);
			}
		}
	}
}
void Options(sf::RenderWindow* window)
{
	

	sf::RectangleShape rect[2];
	sf::Text text[2];
	sf::Font font;
	font.loadFromFile("times.ttf");
	
	for (int i = 0; i < 2; i++)
	{
		text[i].setFont(font);

		rect[i].setOrigin(sf::Vector2f(0, 0));
		rect[i].setPosition(sf::Vector2f(300, 205 + i * 100));
		text[i].setPosition(sf::Vector2f(305, 205 + i * 100));
		text[i].setCharacterSize(80);
		
		
		rect[i].setSize(sf::Vector2f(500, 100));
		rect[i].setOutlineThickness(10);
		rect[i].setOutlineColor(sf::Color::Black);
	}
	text[0].setString("Insert ");
	text[1].setString("Delete ");

	while (window->isOpen())
	{
		window->clear(sf::Color::White);
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		for (int i = 0; i < 2; i++)
		{
			window->draw(rect[i]);
			window->draw(text[i]);
		}



		window->display();
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		for (int i = 0; i < 2; i++)
		{
			if (abs(mousePos.x) > rect[i].getPosition().x && abs(mousePos.x) < (rect[i].getPosition().x + rect[i].getSize().x) && abs(mousePos.y) > (rect[i].getPosition().y + 40) && abs(mousePos.y) < (rect[i].getPosition().y + rect[0].getSize().y + 40))
			{
				rect[i].setFillColor(sf::Color::Green);
				text[i].setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					
						keypad(window,i);
						delay(600);
				}
			}
			else {
				rect[i].setFillColor(sf::Color::Blue);
				text[i].setFillColor(sf::Color::Yellow);
			}
		}

	}
}
void createWindow()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "AVL");
	sf::Text txt;
	sf::Font font;
	font.loadFromFile("times.ttf");
	txt.setFont(font);
	txt.setString("Start");
	txt.setCharacterSize(200);
	sf::RectangleShape Rect;
	Rect.setSize(sf::Vector2f(1000, 300));
	Rect.setPosition(sf::Vector2f(290, 250));
	Rect.setFillColor(sf::Color::Blue);
	txt.setPosition(sf::Vector2f(590, 250));
	txt.setFillColor(sf::Color::Yellow);
	
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		if (abs(mousePos.x) > Rect.getPosition().x && abs(mousePos.x) < (Rect.getPosition().x + Rect.getSize().x) && abs(mousePos.y) > (Rect.getPosition().y + 40) && abs(mousePos.y) < (Rect.getPosition().y + Rect.getSize().y + 40))
		{
			Rect.setFillColor(sf::Color::Green);
			txt.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Options(&window);
				delay(600);
			}

		}
		else {
			Rect.setFillColor(sf::Color::Blue);
			txt.setFillColor(sf::Color::Yellow);
		}
		window.clear(sf::Color::White);
		window.draw(Rect);
		
		window.draw(txt);
		window.display();
	}
}
int main()
{
	createWindow();
}