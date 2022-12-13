#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

void add(
    const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
    std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response) {
  response->sum = request->a + request->b;
  RCLCPP_INFO_STREAM(
      rclcpp::get_logger("rclcpp"),
      "Incoming request: a: " << request->a << " b: " << request->b);
  RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
                     "sending back response: [" << response->sum << "]");
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node{rclcpp::Node::make_shared("add_two_ints_server")};

  auto service{node->create_service<example_interfaces::srv::AddTwoInts>(
      "add_two_ints", &add)};

  RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
  exit(EXIT_SUCCESS);
}
