# Plazza

*It's pizza time*

## Subject

The Plazza is an introduction project to concurrent programming. You have to take pizza ordering from user input and manage processes (kitchens) to efficiently cook pizzas.

## Usage

You'll need [make](https://www.gnu.org/software/make/) and [SFML](https://www.sfml-dev.org/index-fr.php) to compile the project.


```sh
$ git clone https://https://github.com/Harmos274/Plazza/
$ cd Plazza
$ make
$ ./plazza 2 5 2000
```

| Argument   | Explanation                 |
|:----------:|-----------------------------|
| first      | Cooking time multiplier.    |
| second     | Number of cook per kitchen. |
| third      | Ingredient restock couldown.|


## Documentation

### How to add a orderable pizza ?

In `./include/Marmiton.hpp` :

```cpp
constexpr std::array marmiton{
    pizzas::Recipe("margarita",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE,
                   pizzas::bakingTime{1000}),

    pizzas::Recipe("regina",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE | pizzas::ingredient::HAM |
                       pizzas::ingredient::MUSHROOMS,
                   pizzas::bakingTime{2000}),

    pizzas::Recipe("americana",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::GRUYERE | pizzas::ingredient::STEAK,
                   pizzas::bakingTime{2000}),

    pizzas::Recipe("fantasia",
                   pizzas::ingredient::DOE | pizzas::ingredient::TOMATO |
                       pizzas::ingredient::EGGPLANT |
                       pizzas::ingredient::GOAT_CHEESE |
                       pizzas::ingredient::CHIEF_LOVE,
                   pizzas::bakingTime{4000}),
};
```
is a local pizza database. If you want to add a pizza recipe just add a `pizzas::Recipe` line into the array.


| Recipe arguments  |      Corresp      |               Type               |
|:-----------------:|:-----------------:|:--------------------------------:|
| first             |     pizza name    | "Name"                           |
| second            | pizza ingredients | piped `pizzas::ingredient`       |
| third             | pizza baking time | `pizzas::bakingTime{time in ms}` |


Next, **recompile** the project and you will be able to order your pizza at the reception ;) .
<br>
### How to order a pizza ?

While the plazza is running you can order a pizza thanks to the textbox at the top of the window.

The order format is `[PIZZA NAME] [SIZE] x[QUANTITY]`, for example : `americana XXL x15`

You can do multiple order at the same time with `;` : `americana XXL x15 ; fantasia L x10`
In multiple order, if there is an invalid pizza in the line, it will be **ignored**.

When your order is sent, each oppened window shows you a kitchen.
You can directly see the progression of the pizza baking !

If a kitchen doesn't receive an order, it will close after **5 seconds**.
