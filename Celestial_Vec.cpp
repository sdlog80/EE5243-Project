/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TrackingSystem.h"

using namespace std;

Celestial::Celestial(const string Name) : Sim_Name(Name){
    SpaceCount = 0;
    Default.Time = -1;
}

void Celestial::Change_Settings(){
    Orbit_Gen.Set_Defaults();
}

void Celestial::Set_Parameters(){
    string IN;
    cout << "Specify the default time length for simulations\n";
    IN = str_lower(verify_simdouble());
    if(IN == "cancel"){
        cout << "Canceled" << endl;
        return;
    }
    Default.Time = convert(IN);
    
    cout << "Specify the default initial time step for simulations\n";
    IN = str_lower(verify_simdouble());
    if(IN == "cancel"){
        cout << "Canceled" << endl;
        return;
    }    
    Default.h = convert(IN);
    
    cout << "Specify the default max time step for simulations\n";
    IN = str_lower(verify_simdouble());
    if(IN == "cancel"){
        cout << "Canceled" << endl;
        return;
    }    
    Default.hmax = convert(IN);
    
    cout << "Specify the default min time step for simulations\n";
    IN = str_lower(verify_simdouble());
    if(IN == "cancel"){
        cout << "Canceled" << endl;
        return;
    }
    Default.hmin = convert(IN);
    
    cout << "Specify the default error tolerance for simulations\n";
    IN = str_lower(verify_simdouble());
    if(IN == "cancel"){
        cout << "Canceled" << endl;
        return;
    }    
    Default.e = convert(IN);
    
    cout << "Done" << endl;
}

//This code still needs to be commented out
void Celestial::Add_Object(Celestial* Sim){
    Attributes Celestial;
    string IN, Name;
    int Count = 0;
    float Mass, Radius;
    cout << "\nEnter 'Done' when you're done entering objects. Any object that isn't completely specified will not be added." << endl;
    while(true){
        cout << "Objects Added: " << Count << "\n";        
        cout << "Please enter object name.\n";
        cin >> Name;
        if(str_lower(Name) == "done")break;

        bool exist = false;
        //Test whether object currently exists already or not//
        for(CelestialPtr Object : Celestial_Bodies){
            if(Object->get_Name() == IN){
                exist = true;
                break;
            }                
        }
        if(exist){
            cout << "Error, object already exists.\n";
            break;
        }

        IN = "no";
        if(!Celestial_Bodies.empty()){
            cout << "Would you like to launch the Orbit Customizer? (Yes/No)\n";
            IN = yes_no();
        }
        if(IN == "yes"){
            if(Orbit_Gen.Rand_Orbit_Gen(&Celestial, Mass, Radius, Celestial_Bodies, Name))
                break;
            cout << endl;
        }
        else{
            cout << "\nPlease enter Mass value.\n";
            while(true){
                IN = verify_double();
                if(str_lower(IN) == "done" || 0 < convert(IN))break;
                cout << "Invalid value. Enter a positive mass value" << endl;
            }
            if(str_lower(IN) == "done")break;
            Mass = convert(IN);

            cout << "\nPlease enter Rx value.\n";
            IN = verify_double();
            if(str_lower(IN) == "done")break; 
            Celestial.Rx = convert(IN);

            cout << "\nPlease enter Ry value.\n";
            IN = verify_double();
            if(str_lower(IN) == "done")break; 
            Celestial.Ry = convert(IN);

            cout << "\nPlease enter Rz value.\n";
            IN = verify_double();
            if(str_lower(IN) == "done")break; 
            Celestial.Rz = convert(IN);

            cout << "\nPlease enter Vx value.\n";
            IN = verify_double();
            if(str_lower(IN) == "done")break; 
            Celestial.Vx = convert(IN);        

            cout << "\nPlease enter Vy value.\n";
            IN = verify_double();
            if(str_lower(IN) == "done")break; 
            Celestial.Vy = convert(IN); 

            cout << "\nPlease enter Vz value.\n";
            IN = verify_double();
            if(str_lower(IN) == "done")break; 
            Celestial.Vz = convert(IN);          

            cout << "\nPlease enter Radius value.\n";
            while(true){
                IN = verify_double();
                if(str_lower(IN) == "done" || 0 < convert(IN))break;
                cout << "Invalid value. Enter a positive radius value\n";
            }
            if(str_lower(IN) == "done")
                break; 
            Radius = convert(IN);
        }
        Celestial_Bodies.emplace_back(new Celestial_Body(Name, Mass, Celestial, Radius, Sim));
        Count++;
    }  
    cout << "Ok, what now?" << endl;
}

void Celestial::Simulate(){
    if(ObjectTracker.empty())
        cout << "There's nothing to simulate. Add some objects first.\n";
    else{
        if(Default.Time != -1){//Default simulation parameters have been specified//
            cout << "Would you like to use the default simulation parameters?\n";
            if(yes_no() == "yes"){
                Celestial_Bodies[0]->Simulate_Motion(Default.Time, Default.h, Default.hmax, Default.hmin, Default.e);
                return;
            }
        }
        
        double Time, h, hmax, hmin, e;
        string T, H, Hmax, Hmin, E;
        
        cout << "Enter 'Cancel' if you would like to cancel the simulation setup.\n";
        cout << "Please enter the time length (in seconds) of the simulation.\n";;
        T = verify_simdouble();
        if(str_lower(T) == "cancel"){
            cout << "Canceled, what now?" << endl;  
            return;
        }
        Time = convert(T);

        cout << "Please enter the initial time step (in seconds) for the simulation.\n";
        H = verify_simdouble();
        if(str_lower(H) == "cancel"){
            cout << "Canceled, what now?" << endl;  
            return;
        }
        h = convert(H);        

        cout << "Please enter the max time step (in seconds) for the simulation.\n";
        Hmax = verify_simdouble();
        if(str_lower(Hmax) == "cancel"){
            cout << "Canceled, what now?" << endl;  
            return;
        }
        hmax = convert(Hmax);

        cout << "Please enter the min time step (in seconds) for the simulation.\n";
        Hmin = verify_simdouble();
        if(str_lower(Hmin) == "cancel"){
            cout << "Canceled, what now?" << endl;  
            return;
        }
        hmin = convert(Hmin);

        cout << "Please enter the error tolerance for the simulation.\n";
        E = verify_simdouble();
        if(str_lower(E) == "cancel"){
            cout << "Canceled, what now?" << endl;  
            return;
        }
        e = convert(E);        

        Celestial_Bodies[0]->Simulate_Motion(Time,h,hmax,hmin,e);  
    }    
}

void Celestial::View_Objects() const{
    if(!ObjectTracker.empty()){
        cout << "Here is the current status of all celestial objects." << endl;
        Celestial_Bodies[0]->Display_Objects();
    }
    else
        cout << "There are no objects to display. Add some objects first." << endl;
}

void Celestial::View_Object() const{
    string Name;
    cout << "Enter the name of the Celestial Body you would like to display." << endl;
    cin >> Name;
    bool Control = true;
    for(CelestialPtr I : Celestial_Bodies){
        if(Name == I->get_Name()){
            I->display_Object();
            Control = false;            
            break;
        }
    }
    if(Control)
        cout << "Sorry, Celestial Body not found" << endl;
}

string Celestial::get_name() const{ return Sim_Name;}

void Celestial::Remove_Object(){
    if(Celestial_Bodies.empty())
        cout << "There is nothing to remove. Add some objects first." << endl;
    else{
        string Name;
        cout << "Enter the name of the object you would like to remove." << endl;
        cin >> Name;
        bool Control = true;
        int Count = 0;
        for(CelestialPtr I : Celestial_Bodies){
            if(Name == I->get_Name()){
                I->Remove();              
                Celestial_Bodies.erase(Celestial_Bodies.begin() + Count);
                Control = false;
                break;
            }
            Count++;          
        }
        if(Control)
            cout << "Object does not exist." << endl;
        else{
            //Decrement Celestial IDs of each object after 'Count' and decrease SpaceCount by 1//
            if(!Celestial_Bodies.empty())
                Count_Decr(Count);
            cout << "Done. What now?" << endl;
        }
    }
}

void Celestial::Alter_Object(){
    if(Celestial_Bodies.empty())
        cout << "There is nothing to alter. Add some objects first." << endl;
    else{
        string Name;
        string newName;                
        cout << "Please enter the name of the object you would like to alter." << endl;
        cin >> Name;
        int Pos = get_position(Name);
        if(0 <= Pos){
            string Entry;
            double Rad;
            double Mss;
            bool Cancel = false;
            bool name = false;
            bool mass = false;
            bool radius = false;
            Attributes New = ObjectTracker[Pos];
            cout << "If you would like to cancel any changes enter 'cancel'." << endl;
            cout << "If you are done making changes enter 'done'" << endl;
            while(true){
                cout << "Which attributes from " << Name << " would you like to change? (Rx, Ry, Rz, Vx, Vy, Vz, Name, Mass, Radius)" << endl;
                while(true){
                    cin >> Entry;
                    Entry = str_lower(Entry);
                    if(Entry == "name" || Entry == "rx" || Entry == "ry" || Entry == "rz" || Entry == "vx" || Entry == "vy" || Entry == "vz")
                        break;
                    if(Entry == "mass" || Entry == "radius" || Entry == "cancel" || Entry == "done")
                        break;
                    else
                        cout << "Invalid entry. Try again." << endl;
                }    
                if(Entry == "done")
                    break;
                else if(Entry == "cancel"){
                    Cancel = true;
                    break;
                }
                else{
                    if(Entry == "name"){
                        cout << "Please enter a new name" << endl;
                        cin >> newName;
                        name = true;               
                    }
                    else{
                        string newValue;
                        cout << "Please enter a new double value" << endl;
                        if(Entry == "mass" || Entry == "radius"){
                            while(true){
                                newValue = verify_altdouble();
                                if(str_lower(newValue) == "cancel" || 0 < convert(newValue))
                                    break;
                                cout << "Invalid entry. Both the Radius and Mass must be strictly positive." << endl;
                            }                           
                        }
                        else
                            newValue = verify_altdouble();
                        if(str_lower(newValue) == "cancel"){
                            Cancel = true;
                            break;
                        }
                        else{
                            if(Entry == "rx")
                                New.Rx = convert(newValue);
                            if(Entry == "ry")
                                New.Ry = convert(newValue);
                            if(Entry == "rz")
                                New.Rz = convert(newValue);
                            if(Entry == "vx")
                                New.Vx = convert(newValue);
                            if(Entry == "vy")
                                New.Vy = convert(newValue);
                            if(Entry == "vz")
                                New.Vz = convert(newValue);                        
                            if(Entry == "mass"){
                                mass = true;
                                Mss = convert(newValue);
                            }
                            if(Entry == "radius"){
                                radius = true;
                                Rad = convert(newValue);
                            }
                        }                  
                    }                
                }           
            }
            if(!Cancel){                
                ObjectTracker[Pos] = New;
                if(name)//Change name if necessary//
                    Celestial_Bodies[New.ID]->Name = newName;
                if(mass)
                    Celestial_Bodies[New.ID]->Mass = Mss;
                if(radius)
                    Celestial_Bodies[New.ID]->Radius = Rad;
                Celestial_Bodies[New.ID]->Values = New;
                cout << "Done, what now?" << endl;
            }
            else
                cout << "Canceled. Ok what now?" << endl;    
        }
        else
            cout << "Sorry. Object either doesn't exist or was destroyed in a simulation. Add a new one." << endl;
    }
}

int Celestial::get_position(const string name){
    int Counter = 0;
    for(Attributes i : ObjectTracker){
        if(Celestial_Bodies[i.ID]->Name == name)
            return Counter;
        Counter++;
    }
    return -1;
}

void Celestial::Count_Decr(int Decrement){
    int Element = 0;
    for(int i=Decrement; i<Celestial_Bodies.size(); i++){
        Element = 0;
        for(Attributes Tracker : ObjectTracker){
            if(Tracker.ID == Celestial_Bodies[i]->Values.ID){
                Tracker.ID--;
                ObjectTracker[Element] = Tracker;                
                break;
            }
            Element++;
        }
        Celestial_Bodies[i]->Values.ID--;
    }
}

void Init_Sim(Celestial *Sim){    
    Attributes Celestial;
    Celestial.Rx = 0.0; Celestial.Ry = 0.0; Celestial.Rz = 0.0; Celestial.Vx = 0.0; Celestial.Vy = 0.0; Celestial.Vz = 0.0;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Sun",597220000000000000000.0,Celestial,987654321, Sim));
    Celestial.Rx = 70000000000.0; Celestial.Ry = 0.0; Celestial.Rz = 0.0; Celestial.Vx = 0.0; Celestial.Vy = 2385509.050196923; Celestial.Vz = 0.0;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Jupiter", 9237000000000000.0, Celestial, 10000000, Sim));
    Celestial.Rx = 5000000000.0; Celestial.Ry = -50000000000.0; Celestial.Rz = 0.0; Celestial.Vx = 0.0; Celestial.Vy = 50000.0; Celestial.Vz = 0.0;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Earth",500000000000000000000000000000000.0,Celestial,987321, Sim));
    Celestial.Rx = 5007910000; Celestial.Ry = -49956500000; Celestial.Rz = 444010000; Celestial.Vx = 1317430; Celestial.Vy = 7290370; Celestial.Vz = 2172960;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Daniel", 500000, Celestial, 462300, Sim));
    Celestial.Rx = 4235670000; Celestial.Ry = -49653000000; Celestial.Rz = 823960000; Celestial.Vx = 1770000; Celestial.Vy = -753565; Celestial.Vz = -958138;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Michael", 200000, Celestial, 492200, Sim));
    Celestial.Rx = 452450000; Celestial.Ry = 999380000; Celestial.Rz = 944590000; Celestial.Vx = 2.1058; Celestial.Vy = 465134; Celestial.Vz = -4.05;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Thomas", 21600000, Celestial, 1060800, Sim));    
    Celestial.Rx = 700000070.0; Celestial.Ry = 0.0; Celestial.Rz = 800200000; Celestial.Vx = 0.0; Celestial.Vy = 0.0; Celestial.Vz = -50000;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Mars", 600000000.0, Celestial,43553, Sim));    
    Celestial.Rx = 5000000000.0; Celestial.Ry = -50000000000.0; Celestial.Rz = 2000000.0; Celestial.Vx = 0.0; Celestial.Vy = 50000.0; Celestial.Vz = -5000.0;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Moon", 300000.0, Celestial, 10000, Sim));
    Celestial.Rx = 0.0; Celestial.Ry = 0.0; Celestial.Rz = 4248934090.0; Celestial.Vx = 55632.0; Celestial.Vy = 77797.0; Celestial.Vz = -83932;
    Sim->Celestial_Bodies.emplace_back(new Celestial_Body("Venus", 9500000000000.0, Celestial, 800892, Sim));
}
