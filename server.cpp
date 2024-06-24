#include "server.h"

bool debug = true;

std::vector<std::unordered_map<std::string, std::string>> network_topology = {
    {{"Device", "DNS-WebServer (B)"}, {"Interface", "Fa0"}, {"Mode", "Access"}, {"Connected To", "SwitchNetz3"}, {"Connected Interface", "Gig 1/0/1"}, {"VLAN", "VLAN 50"}, {"IP Address", "2001:DB8:3:50::2"}, {"Location", "Berlin"}},
    {{"Device", "SwitchNetz3"}, {"Interface", "Gig1/0/1"}, {"Mode", "Trunk"}, {"Connected To", "RouterNetz3"}, {"Connected Interface", "Gig0/0/0"}, {"VLAN", "VLAN 50/99"}, {"IP Address", ""}, {"Location", "Berlin"}},
    {{"Device", "SwitchNetz3"}, {"Interface", "Fa0"}, {"Mode", "Access"}, {"Connected To", "DNS-Webserver (B)"}, {"Connected Interface", "Fa0"}, {"VLAN", "VLAN 50"}, {"IP Address", ""}, {"Location", "Berlin"}},
    {{"Device", "RouterNetz3"}, {"Interface", "Gig0/0/0"}, {"Mode", "Trunk"}, {"Connected To", "SwitchNetz3"}, {"Connected Interface", "Gig1/0/1"}, {"VLAN", "VLAN 50"}, {"IP Address", "2001:DB8:3:50::1"}, {"Location", "Berlin"}},
    {{"Device", "RouterNetz3"}, {"Interface", "Gig0/0/0"}, {"Mode", "Trunk"}, {"Connected To", "SwitchNetz3"}, {"Connected Interface", "Gig1/0/1"}, {"VLAN", "VLAN 99"}, {"IP Address", "2001:DB8:3:99::1"}, {"Location", "Berlin"}},
    {{"Device", "RouterNetz3"}, {"Interface", "Se0/1/0"}, {"Mode", "Access"}, {"Connected To", "RouterNetz2"}, {"Connected Interface", "Se0/2/0"}, {"VLAN", ""}, {"IP Address", "FD00:2:3::2"}, {"Location", "Berlin"}},
    {{"Device", "RouterNetz3"}, {"Interface", "Se0/1/1"}, {"Mode", "Access"}, {"Connected To", "RouterNetz1"}, {"Connected Interface", "Se0/1/0"}, {"VLAN", ""}, {"IP Address", "FD00:1:3::2"}, {"Location", "Berlin"}},
    {{"Device", "RouterNetz3"}, {"Interface", "Se0/2/0"}, {"Mode", "Trunk"}, {"Connected To", "RouterNetz4"}, {"Connected Interface", "Se0/2/1"}, {"VLAN", ""}, {"IP Address", "FD00:3:4::1"}, {"Location", "Berlin"}},
    {{"Device", "PC0"}, {"Interface", "Fa0"}, {"Mode", "Access"}, {"Connected To", "SwitchNetz1"}, {"Connected Interface", "Gig1/0/1"}, {"VLAN", "VLAN 10"}, {"IP Address", "2001:DB8:1:10::2"}, {"Location", "Hamburg"}},
    {{"Device", "PC1"}, {"Interface", "Fa0"}, {"Mode", "Access"}, {"Connected To", "SwitchNetz1"}, {"Connected Interface", "Gig1/0/2"}, {"VLAN", "VLAN 20"}, {"IP Address", "2001:DB8:1:20::2"}, {"Location", "Hamburg"}},
    {{"Device", "SwitchNetz1"}, {"Interface", "Gig1/0/1"}, {"Mode", "Access"}, {"Connected To", "PC0"}, {"Connected Interface", "Fa0"}, {"VLAN", "VLAN 10"}, {"IP Address", ""}, {"Location", "Hamburg"}},
    {{"Device", "SwitchNetz1"}, {"Interface", "Gig1/0/2"}, {"Mode", "Access"}, {"Connected To", "PC1"}, {"Connected Interface", "Fa0"}, {"VLAN", "VLAN 20"}, {"IP Address", ""}, {"Location", "Hamburg"}},
    {{"Device", "SwitchNetz1"}, {"Interface", "Gig1/0/3"}, {"Mode", "Trunk"}, {"Connected To", "RouterNetz1"}, {"Connected Interface", "Gig0/0/0"}, {"VLAN", "VLAN 10/20/99"}, {"IP Address", ""}, {"Location", "Hamburg"}},
    {{"Device", "RouterNetz1"}, {"Interface", "Gig0/0/0"}, {"Mode", "Trunk"}, {"Connected To", "SwitchNetz1"}, {"Connected Interface", "Gig1/0/3"}, {"VLAN", "VLAN 10"}, {"IP Address", "2001:DB8:1:10::1"}, {"Location", "Hamburg"}},
    {{"Device", "RouterNetz1"}, {"Interface", "Gig0/0/0"}, {"Mode", "Trunk"}, {"Connected To", "SwitchNetz1"}, {"Connected Interface", "Gig1/0/3"}, {"VLAN", "VLAN 20"}, {"IP Address", "2001:DB8:1:20::1"}, {"Location", "Hamburg"}},
    {{"Device", "RouterNetz1"}, {"Interface", "Gig0/0/0"}, {"Mode", "Trunk"}, {"Connected To", "SwitchNetz1"}, {"Connected Interface", "Gig1/0/3"}, {"VLAN", "VLAN 99"}, {"IP Address", "2001:DB8:1:99::1"}, {"Location", "Hamburg"}},
    {{"Device", "RouterNetz1"}, {"Interface", "Se0/2/0"}, {"Mode", "Access"}, {"Connected To", "RouterNetz2"}, {"Connected Interface", "Se0/1/0"}, {"VLAN", ""}, {"IP Address", "FD00:1:2::1"}, {"Location", "Hamburg"}}};

std::vector<std::unordered_map<std::string, std::string>> ipam = {
    {{"Netz", "2001:DB8:1:10::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 10"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Netz fuer Hamburg"}},
    {{"Netz", "2001:DB8:1:10::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 10"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Client 1, Netz fuer Hamburg"}},
    {{"Netz", "2001:DB8:1:20::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 20"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Netz fuer Hamburg"}},
    {{"Netz", "2001:DB8:1:20::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 20"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Client 2, Netz fuer Hamburg"}},
    {{"Netz", "2001:DB8:2:30::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 30"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Netz fuer Luebeck"}},
    {{"Netz", "2001:DB8:2:30::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 30"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Client 3, Netz fuer Luebeck"}},
    {{"Netz", "2001:DB8:2:40::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 40"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Netz fuer Luebeck"}},
    {{"Netz", "2001:DB8:2:40::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 40"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Client 4, Netz fuer Luebeck"}},
    {{"Netz", "2001:DB8:3:50::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 50"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Netz fuer Berlin"}},
    {{"Netz", "2001:DB8:3:50::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 50"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "DNS- und Webserver, Netz fuer Berlin"}},
    {{"Netz", "2001:DB8:4:60::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 60"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Netz fuer Muenchen"}},
    {{"Netz", "2001:DB8:4:60::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 60"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Webserver, Netz fuer Muenchen"}},
    {{"Netz", "2001:DB8:1:99::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Managementnetz Hamburg"}},
    {{"Netz", "2001:DB8:2:99::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Managementnetz Luebeck"}},
    {{"Netz", "2001:DB8:3:99::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Managementnetz Berlin"}},
    {{"Netz", "2001:DB8:4:99::1"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Router, Managementnetz Muenchen"}},
    {{"Netz", "2001:DB8:1:99::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Switch, Managementnetz Hamburg"}},
    {{"Netz", "2001:DB8:2:99::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Switch, Managementnetz Luebeck"}},
    {{"Netz", "2001:DB8:3:99::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Switch, Managementnetz Berlin"}},
    {{"Netz", "2001:DB8:4:99::2"}, {"Subnetzmaske", "64"}, {"VLAN", "VLAN 99"}, {"Kategorie", "Zugangsnetz"}, {"Beschreibung", "Switch, Managementnetz Muenchen"}},
    {{"Netz", "FD00:1:2::1"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Hamburg-Luebeck"}},
    {{"Netz", "FD00:1:2::2"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Luebeck-Hamburg"}},
    {{"Netz", "FD00:1:3::1"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Hamburg-Berlin"}},
    {{"Netz", "FD00:1:3::2"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Berlin-Hamburg"}},
    {{"Netz", "FD00:1:4::1"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Hamburg-Muenchen"}},
    {{"Netz", "FD00:1:4::2"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Muenchen-Hamburg"}},
    {{"Netz", "FD00:2:4::1"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Luebeck-Muenchen"}},
    {{"Netz", "FD00:2:4::2"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Muenchen-Luebeck"}},
    {{"Netz", "FD00:2:3::1"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Luebeck-Berlin"}},
    {{"Netz", "FD00:2:3::2"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Berlin-Luebeck"}},
    {{"Netz", "FD00:3:4::1"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Berlin-Muenchen"}},
    {{"Netz", "FD00:3:4::2"}, {"Subnetzmaske", "64"}, {"VLAN", "Keine"}, {"Kategorie", "Transportnetz"}, {"Beschreibung", "Muenchen-Berlin"}}};

std::string get_response_for_test()
{
    std::string body = "Hello this is a test endpoint!";
    return api::create_response(api::status_code::OK, body, api::content_type::PLAIN);
}

std::string get_response_for_daniel()
{
    Student daniel("Daniel", 14, "ClownSchool");

    auto json = daniel.toJson();
    std::string body = json.dump();

    return api::create_response(api::status_code::OK, body, api::content_type::PLAIN);
}

std::string get_response_for_customer()
{
    Customer streamline("Streamline", "Daniel Auer", 12345);

    auto json = streamline.toJson();
    std::string body = json.dump();

    return api::create_response(api::status_code::OK, body, api::content_type::PLAIN);
}

std::string get_response_for_support()
{
    Customer baltic("B@ltic", "Timo Reiss", 54321);

    auto json = baltic.toJson();
    std::string body = json.dump();

    return api::create_response(api::status_code::OK, body, api::content_type::PLAIN);
}

std::string get_response_for_jsontopology()
{
    std::string json_data = api::convert_vector_to_json(network_topology);

    return api::create_response(api::status_code::OK, json_data, api::content_type::PLAIN);
}

std::string get_response_for_jsonipam()
{
    std::string json_data = api::convert_vector_to_json(ipam);

    return api::create_response(api::status_code::OK, json_data, api::content_type::PLAIN);
}

std::string get_response_for_404()
{
    std::string body = "404 Not Found. Endpoint does not exist.";
    return api::create_response(api::status_code::NOT_FOUND, body, api::content_type::PLAIN);
}

std::string get_connection_by_device(const std::string &device_name)
{
    nlohmann::json result = nlohmann::json::array();

    for (const auto &entry : network_topology)
    {
        if (entry.at("Device") == device_name)
        {
            nlohmann::json connection;
            for (const auto &pair : entry)
            {
                connection[pair.first] = pair.second;
            }
            result.push_back(connection);
        }
    }

    return api::create_response(api::status_code::OK, result.dump(), api::content_type::PLAIN);
}

std::string get_connection_by_interface(const std::string &interface)
{
    nlohmann::json result = nlohmann::json::array();

    for (const auto &entry : network_topology)
    {
        if (entry.at("Interface") == interface)
        {
            nlohmann::json connection;
            for (const auto &pair : entry)
            {
                connection[pair.first] = pair.second;
            }
            result.push_back(connection);
        }
    }

    return api::create_response(api::status_code::OK, result.dump(), api::content_type::PLAIN);
}

std::string generate_network_topology_html()
{
    std::string table_html = R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Port Table</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                background-color: #f0f0f0;
                text-align: center;
                padding: 50px;
            }
            h1 {
                color: #333;
            }
            table {
                margin: 0 auto;
                border-collapse: collapse;
                width: 90%;
                margin-bottom: 20px;
            }
            th, td {
                border: 1px solid #ccc;
                padding: 10px;
                text-align: left;
            }
            th {
                background-color: #007BFF;
                color: white;
            }
            .button {
                display: inline-block;
                padding: 10px 20px;
                margin: 10px;
                font-size: 1em;
                color: white;
                background-color: #007BFF;
                border: none;
                border-radius: 5px;
                text-decoration: none;
                transition: background-color 0.3s;
            }
            .button:hover {
                background-color: #0056b3;
            }
        </style>
    </head>
    <body>
        <h1>Port Table</h1>
        <table>
            <tr>
                <th>Geraet</th>
                <th>Schnittstelle</th>
                <th>Modus</th>
                <th>Verbunden mit</th>
                <th>Schnittstelle</th>
                <th>VLAN</th>
                <th>IP-Adresse</th>
                <th>Standort</th>
            </tr>
    )";

    for (const auto &entry : network_topology)
    {
        table_html += "<tr>";
        table_html += "<td>" + entry.at("Device") + "</td>";
        table_html += "<td>" + entry.at("Interface") + "</td>";
        table_html += "<td>" + entry.at("Mode") + "</td>";
        table_html += "<td>" + entry.at("Connected To") + "</td>";
        table_html += "<td>" + entry.at("Connected Interface") + "</td>";
        table_html += "<td>" + entry.at("VLAN") + "</td>";
        table_html += "<td>" + entry.at("IP Address") + "</td>";
        table_html += "<td>" + entry.at("Location") + "</td>";
        table_html += "</tr>";
    }

    table_html += R"(
        </table>
        <a href="/" class="button">Back Home</a>
    </body>
    </html>
    )";

    return table_html;
}

std::string generate_ipam_html()
{
    std::string table_html = R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>IPAM Table</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                background-color: #f0f0f0;
                text-align: center;
                padding: 50px;
            }
            h1 {
                color: #333;
            }
            table {
                margin: 0 auto;
                border-collapse: collapse;
                width: 90%;
                margin-bottom: 20px;
            }
            th, td {
                border: 1px solid #ccc;
                padding: 10px;
                text-align: left;
            }
            th {
                background-color: #007BFF;
                color: white;
            }
            .button {
                display: inline-block;
                padding: 10px 20px;
                margin: 10px;
                font-size: 1em;
                color: white;
                background-color: #007BFF;
                border: none;
                border-radius: 5px;
                text-decoration: none;
                transition: background-color 0.3s;
            }
            .button:hover {
                background-color: #0056b3;
            }
        </style>
    </head>
    <body>
        <h1>IPAM Table</h1>
        <table>
            <tr>
                <th>Netz</th>
                <th>Subnetzmaske</th>
                <th>VLAN</th>
                <th>Kategorie</th>
                <th>Beschreibung</th>
            </tr>
    )";

    for (const auto &entry : ipam)
    {
        table_html += "<tr>";
        table_html += "<td>" + entry.at("Netz") + "</td>";
        table_html += "<td>" + entry.at("Subnetzmaske") + "</td>";
        table_html += "<td>" + entry.at("VLAN") + "</td>";
        table_html += "<td>" + entry.at("Kategorie") + "</td>";
        table_html += "<td>" + entry.at("Beschreibung") + "</td>";
        table_html += "</tr>";
    }

    table_html += R"(
        </table>
        <a href="/" class="button">Back Home</a>
    </body>
    </html>
    )";

    return table_html;
}

std::string generate_swagger_html(){
    return api::read_file_to_string("../swagger/swagger.html");
}

std::string generate_homepage_html()
{
    std::string table_html = R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Welcome to Streamline Network</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                background-color: #f0f0f0;
                text-align: center;
                padding: 50px;
            }
            h1 {
                color: #333;
            }
            p {
                font-size: 1.2em;
                color: #666;
            }
            .button-container {
                margin-top: 20px;
            }
            .button {
                display: inline-block;
                padding: 10px 20px;
                margin: 10px;
                font-size: 1em;
                color: white;
                background-color: #007BFF;
                border: none;
                border-radius: 5px;
                text-decoration: none;
                transition: background-color 0.3s;
            }
            .button:hover {
                background-color: #0056b3;
            }
        </style>
    </head>
    <body>
        <h1>Welcome to the Streamline network!</h1>
        <p>Headquartered in Hamburg</p>
        <p>Since 2019</p>
        <p>CEO: Marius Jungbauer and Andre Kosmos</p>
        <div class="button-container">
            <a href="/ports" class="button">Port Table</a>
            <a href="/ipam" class="button">IPAM</a>
        </div>
    </body>
    </html>
    )";

    return table_html;
}

void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    std::string request(buffer);
    std::string::size_type pos = request.find("GET ");
    std::string::size_type end = request.find(" HTTP/", pos);

    if (debug)
    {
        const char *requestCString = request.c_str();
        printf("%s\n", requestCString);
    }

    std::string url = request.substr(pos + 4, end - (pos + 4));

    std::string response;

    if (url == "/test")
    {
        response = get_response_for_test();
    }
    else if (url == "/daniel")
    {
        response = get_response_for_daniel();
    }
    else if (url == "/customer")
    {
        response = get_response_for_customer();
    }
    else if (url == "/support")
    {
        response = get_response_for_support();
    }
    else if (url == "/ports")
    {
        std::string html_body = generate_network_topology_html();
        response = api::create_response(api::status_code::OK, html_body, api::content_type::HTML);
    }
    else if (url == "/ipam")
    {
        std::string html_body = generate_ipam_html();
        response = api::create_response(api::status_code::OK, html_body, api::content_type::HTML);
    }
    else if (url == "/")
    {
        std::string html_body = generate_homepage_html();
        response = api::create_response(api::status_code::OK, html_body, api::content_type::HTML);
    }
    else if (url == "/swagger")
    {
        std::string html_body = generate_swagger_html();
        response = api::create_response(api::status_code::OK, html_body, api::content_type::HTML);
    }
    else if (url == "/jsontopology")
    {
        response = get_response_for_jsontopology();
    }
    else if (url.find("/device/") == 0)
    {
        std::string device_name = url.substr(8);
        response = get_connection_by_device(device_name);
    }
    else if (url.find("/interface/") == 0)
    {
        std::string interface = url.substr(11);
        response = get_connection_by_interface(interface);
    }
    else if (url == "/jsonipam")
    {
        response = get_response_for_jsontopology();
    }
    else
    {
        response = get_response_for_404();
    }

    write(client_socket, response.c_str(), response.length());

    close(client_socket);
}

void logPeerInfo(int socket)
{
    struct sockaddr_in client_address;
    socklen_t client_addrlen = sizeof(client_address);
    if (getpeername(socket, (struct sockaddr *)&client_address, &client_addrlen) == 0)
    {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_address.sin_port);

        std::cout << "*** New request by: IP " << client_ip << ", Port " << client_port << " ***"<< std::endl;
    }
    else
    {
        perror("getpeername failed");
    }
}

void start_server()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        if (debug)
        {
            logPeerInfo(new_socket);
        }

        handle_client(new_socket);
    }
}

// Compile: g++ -std=c++11 -o server main.cpp server.cpp