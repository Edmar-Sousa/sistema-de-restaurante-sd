#include "esqueleto.hpp"


std::shared_ptr<std::string> Esqueleto::invoke(std::shared_ptr<Message> message)
{
    switch (message->get_method_id())
    {
        case 1:
            return dispachante.get_tables();
        
        case 2:
        {
            json arguments = json::parse(message->get_arguments());
            json response;

            response["message"] = *dispachante.reserved_table(arguments["client_name"], arguments["table_id"]);

            return std::make_shared<std::string>(response.dump());
        }
        case 3:
        {
            json arguments = json::parse(message->get_arguments());
            json response;

            response["message"] = *dispachante.check_status_order(arguments["table_id"]);

            return std::make_shared<std::string>(response.dump());
        }
        case 4:
        {
            json arguments = json::parse(message->get_arguments());

            json response;
            response["message"] = *dispachante.new_order(arguments["table_id"], arguments["products"]);
            
            return std::make_shared<std::string>(response.dump());
        }
        case 5:
            return dispachante.get_menu();

        default:
            return std::make_shared<std::string>("Metodo não encontrado");
    }
}
