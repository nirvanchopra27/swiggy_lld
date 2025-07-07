#include "common.hpp"
#include "userMgr.hpp"
#include "restaurantMgr.hpp"
#include "deliveryPartnerMgr.hpp"
#include "orderMgr.hpp"

int main() {
	// Chinese Restaurant
	RestaurantOwner* owner1 = new RestaurantOwner("owner1");
	Restaurant* chineseRest = new Restaurant("chinese vala", owner1, new Location(1, 2));
	Dish* noodles = new Dish("noodles", CUISINE::CHINESE, 200);
	noodles->addAddOn({ new DishAddOn("premium sauce", 20) });
	Dish* fried_rice = new Dish("fried rice", CUISINE::CHINESE, 180);
	Dish* spring_rolls = new Dish("spring rolls", CUISINE::CHINESE, 120);
	Menu* chinese_menu = new Menu({ noodles, fried_rice, spring_rolls });
	chineseRest->addMenu(chinese_menu);

	// South Indian Restaurant
	RestaurantOwner* owner2 = new RestaurantOwner("owner2");
	Restaurant* southIndianRest = new Restaurant("south indian food", owner2, new Location(2, 3));
	Dish* idli = new Dish("idli", CUISINE::SOUTH_INDIAN, 200);
	Dish* dosa = new Dish("dosa", CUISINE::SOUTH_INDIAN, 180);
	Dish* uthappam = new Dish("uthappam", CUISINE::SOUTH_INDIAN, 120);
	Menu* south_indian_menu = new Menu({ idli, dosa, uthappam });
	southIndianRest->addMenu(south_indian_menu);

	RestaurantMgr* restaurantMgr = RestaurantMgr::getRestaurantMgr();
	restaurantMgr->addRestaurant("chinese vala", chineseRest);
	restaurantMgr->addRestaurant("south indian food", southIndianRest);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	DeliveryPartner* alpha = new DeliveryPartner("alpha");
	DeliveryPartner* beta = new DeliveryPartner("beta");
	DeliveryPartner* gamma = new DeliveryPartner("gamma");

	DeliveryPartnerMgr* deliveryPartnerMgr = DeliveryPartnerMgr::getDeliveryPartnerMgr();
	deliveryPartnerMgr->addDeliveryPartner("alpha", alpha);
	deliveryPartnerMgr->addDeliveryPartner("beta", beta);
	deliveryPartnerMgr->addDeliveryPartner("gamma", gamma);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	User* nirvan = new User("nirvan", new Location(10, 11));

	UserMgr* userMgr = UserMgr::getUserMgr();
	userMgr->addUser("nirvan", nirvan);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	// Nirvan adds dishes to cart and places order
	std::unordered_map<Dish*, int> cart;
	cart.insert({ noodles, 2 });
	cart.insert({ fried_rice, 1 });

	Order* order1 = new Order(nirvan, chineseRest, cart);

	OrderMgr* orderMgr = OrderMgr::getOrderMgr();
	orderMgr->createOrder("order1", order1);

	return 0;
}
