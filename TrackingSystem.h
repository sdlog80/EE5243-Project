/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrackingSystem.h
 * Author: Michael DeMoor
 *
 * Created on March 28, 2017, 6:35 PM
 */

#ifndef TRACKINGSYSTEM_H
#define TRACKINGSYSTEM_H
#include "Celestial_Vec.h"

class Celestial_Body{friend class Celestial;
    friend std::string Get_Status(CelestialPtr); 
    public:
        Celestial_Body(const std::string, const float, const Attributes, const float, Celestial*);             
        void Display_Objects() const;
        void display_Object() const;
        void Simulate_Motion(double,double,double,double,double);
        //void Run_Simulation(double,double,double,double,double);
        
        //Some Gets//
        Attributes get_attributes() const;                       
        std::string get_Name() const;
        float get_Radius() const;
        float get_Mass() const;
        
    private:      
        void update_attributes();
        void Remove();        
        void print_attributes(Attributes, std::string, float, float) const;              
        //Simulation Support Functions//
        void Initialize_Sim(
        std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&, 
        std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&,
        std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&,
        std::vector<Attributes>&, std::vector<Attributes>&, std::vector<Attributes>&
        );
        std::vector<Attributes>& RK_Functions(std::vector<Attributes>&,std::vector<Attributes>&);
        Position Acceleration(std::vector<Attributes>&, int);
        Position Calculations(Position&, Position&, const float);        
        double Distance_Calc(const double,const double,const double);
        double Get_R(const std::vector<Attributes>&, const double);
        void collision(const double, std::vector<Attributes>&);
        Attributes Momentum(Attributes, Attributes); 
        //Data Members//
        Celestial *Celestial_Vec;        
        std::string Name;
        Attributes Values;
        std::string Status;//Change to bool//
        float Mass;
        float Radius;  
};


#endif /* TRACKINGSYSTEM_H */
//Notes for later:
//Create a stopping thread for simulations//
//Edit the Celestial Simulate function. Create default simulation parameters//
//Fix constructor for Celestial_Body//
//Comment out Celestial.cpp code//
//Remove some unnecessary test code in Sub_Celestial_Body.cpp//
//Change is_collision to collision//