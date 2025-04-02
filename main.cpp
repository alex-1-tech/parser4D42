#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>

#pragma pack(push, 1)
struct TargetData {
    uint8_t id;
    uint16_t vertical_distance;
    uint16_t lateral_distance;
    uint16_t speed_y_direction;
    uint8_t target_type;
    uint8_t lane_number;
    uint16_t front_spacing;
    uint16_t front_time_interval;
    uint16_t speed_x_direction;
    uint16_t heading_angle;
    uint8_t incidents;
    uint32_t radar_x;
    uint32_t radar_y;
    uint8_t blind_mark;
    uint8_t car_length;
    uint8_t car_width;
    // uint16_t module_verification;
};
#pragma pack(pop)

int parse_4D42_block(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: failed to open file!\n";
        return 1;
    }

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    size_t index = 0;
    while (index < data.size() - 4) {
        if (data[index] == 'M' && data[index + 1] == 'B') {
            std::cout << "The 4D42 (MB) block was found,";
            index += 2;

            uint16_t block_length;
            std::memcpy(&block_length, &data[index], sizeof(uint16_t));
            index += 2;
            std::cout << " length=" << block_length << ".\n";
            size_t end_index = index + block_length - 2;

            while (index + sizeof(TargetData) <= end_index) {
                TargetData target_data{};
                std::memcpy(&target_data, &data[index], sizeof(TargetData));
                index += sizeof(TargetData);
                std::cout << "Id " << static_cast<int>(target_data.id) << ":\n";
                std::cout << "  Vertical distance: " << target_data.vertical_distance * 0.1 << " m\n";
                std::cout << "  Lateral distance: " << target_data.lateral_distance * 0.1 << " m\n";
                std::cout << "  Speed (y direction): " << target_data.speed_y_direction * 0.1 << " m/s\n";
                std::cout << "  Target type: " << static_cast<int>(target_data.target_type) << "\n";
                std::cout << "  Lane number: " << static_cast<int>(target_data.lane_number) << "\n";
                std::cout << "  Front spacing: " << target_data.front_spacing * 0.1 << " m\n";
                std::cout << "  Front time interval: " << target_data.front_time_interval * 0.1 << " s\n";
                std::cout << "  Speed (x direction): " << target_data.speed_x_direction * 0.1 << " m/s\n";
                std::cout << "  Heading angle: " << target_data.heading_angle << "\n";
                std::cout << "  Incidents: " << static_cast<int>(target_data.incidents) << "\n";
                std::cout << "  Radar X: " << target_data.radar_x * 0.1 << " m\n";
                std::cout << "  Radar Y: " << target_data.radar_y * 0.1 << " m\n";
                std::cout << "  Blind Mark: " << static_cast<int>(target_data.blind_mark) << "\n";
                std::cout << "  Car length: " << target_data.car_length * 0.1 << " m\n";
                std::cout << "  Car width: " << target_data.car_width * 0.1 << " m\n";
                // std::cout << "  Module verification: " << target_data.module_verification * 0.1 << " m\n";
                std::cout << "----------------------------------------\n";
            }
        } else {
            index++;
        }
    }

    return 0;
}

int main() {
    return parse_4D42_block("../b4a2a978-fd42-489b-bc7d-c0eaffef9311.bin");
}
