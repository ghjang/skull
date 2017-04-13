#include "../catch.hpp"

#include <iostream>
#include <memory>

#include "skull/prelude.h"
using namespace skull::prelude;


// top-level base class
struct component
{
    virtual ~component() { }

    virtual void draw() = 0;
};


// intermediate abstract base classes
struct window : component
{ /* ... */ };

struct button : component
{ /* ... */ };

struct scroll_bar : component
{ /* ... */ };


// concrete classes for Mac
struct mac_window : window
{
    void draw() override
    { std::cout << "mac_window::draw()\n"; }
};

struct mac_button : button
{
    void draw() override
    { std::cout << "mac_button::draw()\n"; }
};

struct mac_scroll_bar : scroll_bar
{
    void draw() override
    { std::cout << "mac_scroll_bar::draw()\n"; }
};


// concrete classes for Windows
struct win_window : window
{
    void draw() override
    { std::cout << "win_window::draw()\n"; }
};

struct win_button : button
{
    void draw() override
    { std::cout << "win_button::draw()\n"; }
};

struct win_scroll_bar : scroll_bar
{
    void draw() override
    { std::cout << "win_scroll_bar::draw()\n"; }
};


//==============================================================================
// Implementing the abstract factory pattern in a trivial way

struct component_factory
{
    virtual ~component_factory() { }

    virtual window * create_window() = 0;
    virtual button * create_button() = 0;
    virtual scroll_bar * create_scroll_bar() = 0;
};


struct component_factory_for_mac : component_factory
{
    window * create_window() override
    { return new mac_window{}; }

    button * create_button() override
    { return new mac_button{}; }

    scroll_bar * create_scroll_bar() override
    { return new mac_scroll_bar{}; }
};


struct component_factory_for_win : component_factory
{
    window * create_window() override
    { return new win_window{}; }

    button * create_button() override
    { return new win_button{}; }

    scroll_bar * create_scroll_bar() override
    { return new win_scroll_bar{}; }
};


TEST_CASE("trivial abstract factory", "[example]")
{
    std::unique_ptr<component_factory> ptrFactory;

    // for Mac
    ptrFactory.reset(new component_factory_for_mac{});

    // somewhere in other codes
    {
        std::unique_ptr<window> ptrWindow{ ptrFactory->create_window() };
        std::unique_ptr<button> ptrButton{ ptrFactory->create_button() };
        std::unique_ptr<scroll_bar> ptrScrollBar{ ptrFactory->create_scroll_bar() };

        // ...

        /*
        ptrWindow->draw();
        ptrButton->draw();
        ptrScrollBar->draw();
        */
    }

    // for Windows
    ptrFactory.reset(new component_factory_for_win{});

    // somewhere in other codes. just a copy of the above code block.
    {
        std::unique_ptr<window> ptrWindow{ ptrFactory->create_window() };
        std::unique_ptr<button> ptrButton{ ptrFactory->create_button() };
        std::unique_ptr<scroll_bar> ptrScrollBar{ ptrFactory->create_scroll_bar() };

        // ...

        /*
        ptrWindow->draw();
        ptrButton->draw();
        ptrScrollBar->draw();
        */
    }
}


//==============================================================================
// Implementing the abstract factory pattern in a generic way

// helper classes for class hierarchy generation

struct empty_base
{ };

template <typename T, typename Base>
struct h_wrap : T, Base
{ };


// abstract factory interface generation through class composition.

template <typename Component>
struct factory
{
    virtual ~factory() { };

    virtual Component * create(id<Component>) = 0;

    Component * create()
    { return create(id<Component>{}); }
};


template <typename Base, typename T>
struct create_factory_interface
        : type_is<
            h_wrap<
                factory<T>,
                Base
            >
          >
{ };


template <typename AbstractComponentList>
struct abstract_factory;

template <typename... AbstractComponent>
struct abstract_factory<TL<AbstractComponent...>>
        : foldl_t<
            quote<create_factory_interface>,    // binary metafunction
            empty_base,                         // left-side accumulation
            TL<AbstractComponent...>
          >
{
    using abstract_component_list_t = TL<AbstractComponent...>;

    // NVI(Non-Vitual Interface) for creating the components
    template <typename TargetAbstractComponent>
    TargetAbstractComponent *
    create()
    {
        static_assert(
            elem_v<TargetAbstractComponent, TL<AbstractComponent...>>,
            "The requested component should be one of the abstract components."
        );

        // call the actual factory method
        return static_cast<
                    factory<TargetAbstractComponent> *
               >(this)->create();
    }
};


// concrete factory implementation through class composition

// NOTE: This is for vertical class hierarchy generation.
template <typename Base, typename ComponentPair>
struct concrete_factory_impl : Base
{
    static_assert(length_v<ComponentPair> == 2);

    using target_abstract_component_t = head_t<ComponentPair>;
    using target_concrete_component_t = last_t<ComponentPair>;

    static_assert(
        std::is_base_of_v<
                target_abstract_component_t,
                target_concrete_component_t
        >,
        "abstract component and concrete component should be compatible."
    );

    target_concrete_component_t *
    create(id<target_abstract_component_t>) override
    {
        return new target_concrete_component_t{};
    }
};


template <typename Base, typename ComponentPair>
struct implement_concrete_factory
        : type_is<
            concrete_factory_impl<
                Base,
                ComponentPair
            >
          >
{ };


template
<
    typename AbstractFactoryInterface,
    typename ConcreateComponentList
>
struct concrete_factory;

template
<
    typename AbstractFactoryInterface,
    typename... ConcreteComponent
>
struct concrete_factory<AbstractFactoryInterface, TL<ConcreteComponent...>>
        : foldl_t<
            quote<
                implement_concrete_factory  // binary metafunction.
            >,
            AbstractFactoryInterface,       // left-side accumulation.
                                            // AbstractFactoryInterface will be
                                            // the top-most base class for this factory.
            zip_t<
                typename AbstractFactoryInterface::abstract_component_list_t,
                TL<ConcreteComponent...>
            >
          >
{
    using acl_t = typename AbstractFactoryInterface::abstract_component_list_t;

    static_assert(
        length_v<acl_t> == sizeof...(ConcreteComponent),
        "The number of abstract components should be same as the number of the concrete components."
    );

    using base_derived_test_result_t = zipWith_t<
                                            quote<std::is_base_of>,
                                            acl_t,
                                            TL<ConcreteComponent...>
                                       >;

    static_assert(
        length_v<acl_t> == sum_v<base_derived_test_result_t>,
        "Some in-compatible components is supplied."
    );
};


TEST_CASE("generic abstract factory", "[example]")
{
    //==========================================================================
    // generic abstract factory interface
    using af_interface_t = abstract_factory<
                                TL<window, button, scroll_bar>
                           >;

    //==========================================================================
    // concrete factory for Mac
    using mac_factory_t = concrete_factory<
                                af_interface_t,
                                TL<mac_window, mac_button, mac_scroll_bar>
                          >;

    // NOTE: This is an expected compile error.
    /*
    using mac_factory_1_t = concrete_factory<
                                af_interface_t,
                                TL<mac_window, mac_button>  // not enough
                                                            // concrete components
                            >;
    auto mac_f1 = mac_factory_1_t{};
    */

    // NOTE: This is an expected compile error.
    /*
    using mac_factory_2_t = concrete_factory<
                                af_interface_t,
                                TL<
                                    mac_window,
                                    mac_button,
                                    mac_button  // The third component should be
                                                // derived from scroll_bar class.
                                >
                            >;
    auto mac_f2 = mac_factory_2_t{};
    */

    // NOTE: mac_factory_3_t is a type alias for a wrong type.
    //          But the type alias itself doesn't cause the compile error.
    using mac_factory_3_t = concrete_factory<
                                af_interface_t,
                                TL<
                                    mac_window,
                                    mac_button,
                                    mac_button  // The third component should be
                                                // derived from scroll_bar class.
                                >
                            >;    

    //==========================================================================
    // concrete factory for Windows
    using win_factory_t = concrete_factory<
                                af_interface_t,
                                TL<win_window, win_button, win_scroll_bar>
                          >;

    //==========================================================================
    // some test codes for the factories

    std::unique_ptr<af_interface_t> ptrFactory;

    // for Mac
    ptrFactory.reset(new mac_factory_t{});

    // somewhere in other codes
    {
        std::unique_ptr<window> ptrWindow{ ptrFactory->create<window>() };
        std::unique_ptr<button> ptrButton{ ptrFactory->create<button>() };
        std::unique_ptr<scroll_bar> ptrScrollBar{ ptrFactory->create<scroll_bar>() };

        // ...

        ptrWindow->draw();
        ptrButton->draw();
        ptrScrollBar->draw();
    }

    // for Windows
    ptrFactory.reset(new win_factory_t{});

    // somewhere in other codes. just a copy of the above code block.
    {
        std::unique_ptr<window> ptrWindow{ ptrFactory->create<window>() };
        std::unique_ptr<button> ptrButton{ ptrFactory->create<button>() };
        std::unique_ptr<scroll_bar> ptrScrollBar{ ptrFactory->create<scroll_bar>() };

        // ...

        ptrWindow->draw();
        ptrButton->draw();
        ptrScrollBar->draw();
    }

    // NOTE: This is possbile the abstract factory interface is generated
    //          with the horizontal wrap.
    factory<button> * pButtonFactory = static_cast<
                                            factory<button> *
                                       >(ptrFactory.get());
    std::unique_ptr<button> ptrButton{ pButtonFactory->create() };
    ptrButton->draw();
}
