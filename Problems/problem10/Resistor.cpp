#include "Resistor.hpp"
#include <stdexcept>

void Resistor::set_value(double r)
{
  // TODO
  if(get_value() < 0){
    throw std::invalid_argument("no");
  } 
  set_value(r);

}

double Resistor::get_current() const
{
  // TODO
  if(get_value() == 0){
    throw std::logic_error("no");
  }
  return (get_voltage() / get_value());
}