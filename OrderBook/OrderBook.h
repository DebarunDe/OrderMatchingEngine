#ifndef ORDERBOOK_H
#define ORDERBOOK_H

//include section
#include <cstdint>
#include <vector>
#include <exception>
#include <stdexcept>
#include <memory>

enum OrderType {
    ImmediateOrCancel, //Immediate fill all or part of order, cancel rest
    GoodForDay, //Good until filled or untill end of day
    GoodTilCancel, //Good until filled or canceled
    AllOrNone //filled in entirety, or cancelled
    //Not doing OneCancelsTheOther as it requires 2 orders being inputted to function correctly
};

enum Side {
    Buy,
    Sell
};

using Price     = std::int32_t;
using Quantity  = std::uint32_t;
using OrderID   = std::uint64_t;
struct Level {
    Price price;
    Quantity quantity;
};
using Levels = std::vector<Level>;

class OrderBookLevels {
    private:
        Levels bids_;
        Levels asks_;
    public:
        OrderBookLevels (const Levels& bids,const Levels& asks):
        bids_ { bids },
        asks_ { asks }
        { }
        
        const Levels& getBids() const { return bids_; }
        const Levels& getAsks() const { return asks_; }
};

class Order {
    private:
        OrderID     orderID_;
        OrderType   orderType_;
        Side        side_;
        Price       price_;
        Quantity    quantity_;
    
    public:
        Order (const OrderID& orderID, const OrderType& orderType, const Side& side, const Price& price, const Quantity& quantity):
        orderID_ { orderID },
        orderType_ { orderType },
        side_ { side },
        price_ { price },
        quantity_ { quantity }
        { }

        const OrderID& getOrderID()     const { return orderID_; }
        const OrderType& getOrderType() const { return orderType_; }
        const Side& getSide()           const { return side_; }
        const Price& getPrice()         const { return price_; }
        const Quantity& getQuantity()   const { return quantity_; }
        void Fill(Quantity quantity) {
            if (getQuantity() < quantity)
                throw std::logic_error("Quantity to fill exceeds available quantity for order ID: " + std::to_string(orderID_));
            
            quantity_ -= quantity;
        }
};
using OrderPtr = std::shared_ptr<Order>;
using OrderPtrs = std::vector<OrderPtr>;

/* TODO:
* Generate a Order Class abstraction to allow for cancelling, adding, and Modfying an order
* Generate a trades class that will show trades pending to be done, and store them into a datastructure
* Generate the orderbook class that will deal with everything we need to make this project functional
*/


#endif //ORDERBOOK_H