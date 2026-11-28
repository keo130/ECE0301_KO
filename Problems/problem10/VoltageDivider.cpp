    #include "VoltageDivider.hpp"
    #include <stdexcept>

    VoltageDivider::VoltageDivider(double vs, double* r, int n) : Network(n + 1, n + 1){
    
        if(n < 1){
            throw std::invalid_argument("no");
        }
        VoltageSource *source = new VoltageSource();
        set_component(0,source);
        set_component_value(0,vs);

        for(int i = 0; i < n; i++){
            Resistor *resist = new Resistor();
            set_component(i+1, resist);
            set_component_value(i+1, r[i]);
        }
        
        connect_component_terminal_a(0, 0);
        connect_component_terminal_b(0, 1);

        for(int i = 0; i < get_num_components() - 1; i++){
            if(i == n - 1){
                connect_component_terminal_a(i + 1, 0);
            } else {
            connect_component_terminal_a(i+1, i+2);
        }
            connect_component_terminal_b(i+1, i+1);
            
        }


        //node voltage calculator
        double totalResistance = 0, current = 0; 
        
        set_node_voltage(0,0);
        set_node_voltage(1,get_component_value(0));
        for(int j = 0; j < get_num_resistors(); j++){
            totalResistance = totalResistance + get_component_value(j+1);
        }
        current = get_component_value(0) / totalResistance;
        
        for(int x = 2; x < get_num_nodes(); x++){
        set_node_voltage(x, get_node_voltage(x - 1) - current * get_component_value(x - 1));
        }
    }

    int VoltageDivider::get_num_resistors() const{
        return (get_num_components()-1);
    }

    double VoltageDivider::get_source_voltage() const{
        return get_component_value(0);
    }

    double VoltageDivider::get_loop_current() const{
        return get_component_current(1);
    }

    double VoltageDivider::get_resistance(int i) const{
        if(i < 0 || i >= get_num_resistors()){
            throw std::out_of_range("no");
        } 
        return get_component_value(i+1);
    }

    double VoltageDivider::get_resistor_voltage(int i) const{
        if(i < 0 || i >= get_num_resistors()){
            throw std::out_of_range("no");
        } 
        return get_component_voltage(i+1);
    }

    void VoltageDivider::set_source_voltage(double v){
        set_component_value(0,v);

        //node voltage calculator
        double totalResistance = 0, current = 0; 
        
        set_node_voltage(0,0);
        set_node_voltage(1,get_component_value(0));
        for(int j = 0; j < get_num_resistors(); j++){
            totalResistance = totalResistance + get_component_value(j+1);
        }
        current = get_component_value(0) / totalResistance;
        
        for(int x = 2; x < get_num_nodes(); x++){
        set_node_voltage(x, get_node_voltage(x - 1) - current * get_component_value(x - 1));
        }
    }

    void VoltageDivider::set_resistance(int i, double v){
        if(i < 0 || i >= get_num_resistors()){
            throw std::out_of_range("no");
        }
        set_component_value(i+1, v);

        //node voltage calculator
        double totalResistance = 0, current = 0; 
        
        set_node_voltage(0,0);
        set_node_voltage(1,get_component_value(0));
        for(int j = 0; j < get_num_resistors(); j++){
            totalResistance = totalResistance + get_component_value(j+1);
        }
        current = get_component_value(0) / totalResistance;
        
        for(int x = 2; x < get_num_nodes(); x++){
        set_node_voltage(x, get_node_voltage(x - 1) - current * get_component_value(x - 1));
        }
    }