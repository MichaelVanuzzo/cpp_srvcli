#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
                       "usage: add_two_ints_client X Y");
    exit(EXIT_FAILURE);
  }

  auto node{rclcpp::Node::make_shared("add_two_ints_client")};
  auto client{
      node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints")};

  auto request{
      std::make_shared<example_interfaces::srv::AddTwoInts::Request>()};
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR_STREAM(
          rclcpp::get_logger("rclcpp"),
          "Interrupted while waiting for the service. Exiting.");
      exit(EXIT_FAILURE);
    }
    RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
                       "service not available, waiting again...");
  }

  auto result{client->async_send_request(request)};
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
                       "Sum: " << result.get()->sum);
  } else {
    RCLCPP_ERROR_STREAM(rclcpp::get_logger("rclcpp"),
                        "Failed to call service add_two_ints");
  }

  rclcpp::shutdown();
  exit(EXIT_SUCCESS);
}
