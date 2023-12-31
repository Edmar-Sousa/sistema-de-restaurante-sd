#include "Order.hpp"


Order::Order(int table_id, float order_price, float preparation_time, std::vector<int> products_ids, OrderStatus status)
{
    this->table_id = table_id;
    this->order_price = order_price;
    this->preparation_time = preparation_time;
    this->status = status;
    this->products_ids = std::make_shared<std::vector<int>>(products_ids);
}



std::vector<int> Order::get_products()
{
    return *this->products_ids;
}


OrderStatus Order::get_status()
{
    return this->status;
}
