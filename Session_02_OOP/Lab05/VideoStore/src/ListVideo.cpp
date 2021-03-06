/**
 * Created on 11/01/2021 
*/

#include "ListVideo.h"

ListVideo::ListVideo()
{
    this->head = NULL; 
    this->size = 0; 
}

ListVideo::ListVideo(Video* video)
{
    this->head = new NodeVideo(video); 
    this->size = 1;
}

ListVideo::~ListVideo()
{
    NodeVideo* p = this->head;
    while(p)
    {
        NodeVideo* q = p;
        p = p->getNext();

        delete q;
    }

    this->head = NULL;
    this->size = 0;
}

void ListVideo::setHead(NodeVideo* nodeVideo)
{
    this->head = nodeVideo;
}

NodeVideo* ListVideo::getHead()
{
    return this->head;
}

int ListVideo::getSize()
{
    return this->size;
}

void ListVideo::AddHead(Video* video)
{
    if(this->head == NULL)
    {
        this->head = new NodeVideo(video);
        this->size = 1;
    }
    else
    {
        NodeVideo* p = new NodeVideo(video);
        p->setNext(this->head);
        this->head = p;
        this->size++;
    }
}

NodeVideo* ListVideo::Find(Video* video)
{
    NodeVideo* p = this->head;
    while(p)
    {
        if(p->getVideo()->getID() == video->getID())
            return p;
        p = p->getNext();
    }
    return NULL;
}

NodeVideo* ListVideo::Find(ID* id)
{
    NodeVideo* p = this->head;
    while(p)
    {
        if(p->getVideo()->getID() == *id)
            return p;
        p = p->getNext();
    }
    return NULL;
}

void ListVideo::Remove(Video* video)
{
    NodeVideo* q = this->Find(video);

    if(q != NULL)
    {
        if(this->head == q)
        {
            NodeVideo* p = this->head; 
            this->head = this->head->getNext();

            delete p;
            p = NULL;

            this->size--;
        }
        else
        {
            NodeVideo* p = this->head;

            while (p)
            {
                if(p->getNext() == q)
                {
                    p->setNext(q->getNext());

                    delete q; 
                    q = NULL;

                    this->size--;
                    return;
                }
            }
        }
    }
}

void ListVideo::LoadFromFile(string fileName)
{
    fstream f(fileName, ios::in);
    if(f.is_open())
    {
        string line;
        while(getline(f, line))
        {
            if(line[0] == '#')
                continue;
            
            string sObject[MAX];
            int n;

            Split(line, ',', sObject, n);

            Video* object;
            if (sObject[2] == "DVD")
            {
                object = new DVD(sObject[0], sObject[1], sObject[2], sObject[3], stoi(sObject[4]), stof(sObject[5]), sObject[6]);
            }
            else if (sObject[2] == "Record")
            {
                object = new MovieRecord(sObject[0], sObject[1], sObject[2], sObject[3], stoi(sObject[4]), stof(sObject[5]), sObject[6]);
            }
            else if (sObject[2] == "Game")
            {
                object = new Game(sObject[0], sObject[1], sObject[2], sObject[3], stoi(sObject[4]), stof(sObject[5]));
            }
            
            this->AddHead(object);
        }
        
        f.close();
    }
    else
    {
        cout << "Cannot access file " << fileName << endl;
    }   
}

void ListVideo::SaveToFile(string fileName)
{
    fstream f(fileName, ios::out | ios::trunc);

    if(f.is_open())
    {
        for(NodeVideo* p = this->head; p != NULL; p = p->getNext())
        {
            f << p->getVideo()->toString() << endl;
        }
    }
    else
    {
        cout << "Cannot access file " << fileName << endl;
    }
    
}

void ListVideo::Print()
{
    NodeVideo* p = this->head;

    while (p)
    {
        cout << p->getVideo()->toString() << endl;
        p = p->getNext();
    }
}

void ListVideo::Action()
{
    int numChoose; 
    cout << "--- ITEM action ---" << endl;
    cout << "\t 1. Create new DVD Item" << endl;
    cout << "\t 2. Create new Movie Record" << endl;
    cout << "\t 3. Create new Game" << endl;
    cout << "\t 4. Update item" << endl;
    cout << "\t 5. Delete item" << endl;
    cout << "=> Choose: ";
    cin >> numChoose;

    switch (numChoose)
    {
    case 1:
        this->CreateDVD();
        cout << endl << "Create new DVD Item is success" << endl;
        break;
    case 2:
        this->CreateMovieRecord();
        cout << endl << "Create new Movie Record Item is success" << endl;
        break;
    case 3:
        this->CreateGame();
        cout << endl << "Create new Game Item is success" << endl;
        break;
    case 4: 
        this->UpdateVideo();
        break;
    case 5:
        this->DeleteItem();
        break;
    }
}

void ListVideo::DeleteItem()
{
    string sID;
    cout << "Enter ID: "; 
    cin >> sID;

    ID* id = new ID(sID);

    NodeVideo* removedVideo = this->Find(id);
    if(removedVideo == NULL)
    {
        cout << "Cannot found Item with ID " << id->toString() << endl;
        return;
    }
    else
    {
        this->Remove(removedVideo->getVideo());
        cout << "Delete item is success" << endl;
    }
}

void ListVideo::CreateDVD()
{
    DVD* video = new DVD(); 
    video->Input();
    video->setRental("DVD");

    this->AddHead(video);
}

void ListVideo::CreateMovieRecord()
{
    MovieRecord* video = new MovieRecord(); 
    video->Input();
    video->setRental("Record");

    this->AddHead(video);
}

void ListVideo::CreateGame()
{
    Game* video = new Game(); 
    video->Input();
    video->setRental("Game");

    this->AddHead(video);
}

void ListVideo::UpdateVideo()
{
    string sID;
    cout << "Enter ID of updated video: "; 
    cin >> sID;

    ID* id = new ID(sID);

    NodeVideo* updatedVideo = this->Find(id);
    
    if(updatedVideo == NULL)
    {
        cout << "Cannot found Item with ID " << id->toString() << endl;
        return;
    }
    cout << "Current Information of ITEM" << endl;
    this->PrintOneNodeVideo(updatedVideo);

    cout << "-- Enter new information for ITEM with ID " << updatedVideo->getVideo()->getID().toString() << " --" <<endl;

    string temp;
    cout << "Enter title: "; 
    cin >> ws;
    getline(cin, temp);
    updatedVideo->getVideo()->setTitle(temp);

    cout << "Enter loan type: ";
    cin >> ws;
    getline(cin, temp);
    fflush(stdin);
    updatedVideo->getVideo()->setLoanType(temp);

    int inStock;
    cout << "Enter in-stock: ";
    cin >> inStock;
    updatedVideo->getVideo()->setInStock(inStock);

    float fee;
    cout << "Enter fee: ";
    cin >> fee;
    updatedVideo->getVideo()->setFee(fee);

    cout << "After update information for ITEM with ID " << updatedVideo->getVideo()->getID().toString() << endl;
    this->PrintOneNodeVideo(updatedVideo);
}

void ListVideo::PrintOneNodeVideo(NodeVideo* nodeVideo)
{
    cout << "\tID: " << nodeVideo->getVideo()->getID().toString() << endl;
    cout << "\tTitle: " << nodeVideo->getVideo()->getTitle() << endl;
    cout << "\tRental Type: " << nodeVideo->getVideo()->getRental() << endl;
    cout << "\tLoan Type: " << nodeVideo->getVideo()->getLoanType() << endl;
    cout << "\tIn-Stock: " << nodeVideo->getVideo()->getInStock() << endl;
    cout << "\tFee: " << nodeVideo->getVideo()->getFee() << endl;
    string isAvailable = (nodeVideo->getVideo()->getIsAvailable() == 1) ? "true" : "false";
    cout << "\tIs available: " << isAvailable << endl;
    
    if(nodeVideo->getVideo()->getRental() == "DVD")
        cout << "\tGenres: " << ((DVD*)nodeVideo->getVideo())->getGenres();
    else if (nodeVideo->getVideo()->getRental() == "Record")
        cout << "\tGenres: " << ((MovieRecord*)nodeVideo->getVideo())->getGenres();
}

void ListVideo::PrintAllItem()
{
    for(NodeVideo* p = this->head; p != NULL; p = p->getNext())
    {
        cout << p->getVideo()->toString() << endl;
    }
}

void ListVideo::PrintItemOutOfStock()
{
    for(NodeVideo* p = this->head; p != NULL; p = p->getNext())
    {
        if(p->getVideo()->getInStock() <= 0)
            cout << p->getVideo()->toString() << endl;
    }
}

void ListVideo::SearchByID()
{
    string sID;
    cout << "Enter ID of item: "; 
    cin >> sID;

    ID* id = new ID(sID);

    NodeVideo* nodeVideo = this->Find(id);
    
    if(nodeVideo == NULL)
    {
        cout << "Cannot found Item with ID " << id->toString() << endl;
        return;
    }
    else
    {
        this->PrintOneNodeVideo(nodeVideo);
        cout << endl;
    }
}

void ListVideo::SearchByTitle()
{
    string sName;
    cout << "Enter Title of item: "; 
    cin >> ws;
    getline(cin, sName);

    NodeVideo* nodeVideo = NULL;

    for(NodeVideo* p = this->head; p != NULL; p = p->getNext())
    {
        if(p->getVideo()->getTitle() == sName)
            nodeVideo = p;
    }
    
    if(nodeVideo == NULL)
    {
        cout << "Cannot found Item with Name " << sName << endl;
        return;
    }
    else
    {
        this->PrintOneNodeVideo(nodeVideo);
        cout << endl;
    }
}
