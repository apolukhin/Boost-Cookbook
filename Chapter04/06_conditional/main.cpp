namespace detail {
    struct pre_inc_functor {
    template <class T>
        void operator()(T& value) const {
           ++ value;
        }
    };

    struct post_inc_functor {
    template <class T>
        void operator()(T& value) const {
            value++;
        }
    };

    struct plus_assignable_functor {
    template <class T>
        void operator()(T& value) const {
            value += T(1);
        }
    };

    struct plus_functor {
    template <class T>
        void operator()(T& value) const {
            value = value + T(1);
        }
    };
}

#include <boost/config.hpp> // TODO: remove me after https://github.com/boostorg/type_traits/pull/37 merge

#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/type_traits/has_pre_increment.hpp>

template <class T>
void inc(T& value) {
    // call ++value
    // or call value ++
    // or value += T(1);
    // or value = value + T(1);

    typedef detail::plus_functor step_0_t;

    typedef typename boost::conditional<
      boost::has_plus_assign<T>::value,
      detail::plus_assignable_functor,
      step_0_t
    >::type step_1_t;

    typedef typename boost::conditional<
      boost::has_post_increment<T>::value,
      detail::post_inc_functor,
      step_1_t
    >::type step_2_t;

    typedef typename boost::conditional<
      boost::has_pre_increment<T>::value,
      detail::pre_inc_functor,
      step_2_t
    >::type step_3_t;

    step_3_t()   // Default construction of the functor.
        (value); // Calling operator() of the functor.
}

struct has_only_postinc {
    has_only_postinc operator ++(int) {
        return *this;
    }
};

struct has_only_plus {
    explicit has_only_plus(int){}
};

has_only_plus operator + (has_only_plus v1, has_only_plus ) {
    return v1;
}

#include <boost/mpl/if.hpp>
template <class T>
void inc_mpl(T& value) {
    typedef detail::plus_functor step_0_t;

    typedef typename boost::mpl::if_<
      boost::has_plus_assign<T>,
      detail::plus_assignable_functor,
      step_0_t
    >::type step_1_t;

    typedef typename boost::mpl::if_<
      boost::has_post_increment<T>,
      detail::post_inc_functor,
      step_1_t
    >::type step_2_t;

    typedef typename boost::mpl::if_<
      boost::has_pre_increment<T>,
      detail::pre_inc_functor,
      step_2_t
    >::type step_3_t;

    step_3_t()   // Default construction of the functor.
        (value); // Calling operator() of the functor.
}

#if __cplusplus > 201601L

template <class T>
void inc_cpp17(T& value) {
    if constexpr (boost::has_pre_increment<T>()) {
        ++value;
    } else if constexpr (boost::has_post_increment<T>()) {
        value++;
    } else if constexpr(boost::has_plus_assign<T>()) {
        value += T(1);
    } else {
        value = value + T(1);
    }
}

#endif

#include <cassert>
int main() {
    int i = 0;
    inc(i);
    assert(i == 1);

    has_only_postinc pi;
    inc(pi);

    has_only_plus v(0);
    inc(v);

    inc_mpl(i);
    assert(i == 2);
    inc_mpl(pi);
    inc_mpl(v);

#if __cplusplus > 201601L
    inc_cpp17(i);
    assert(i == 3);
    inc_cpp17(pi);
    inc_cpp17(v);
#endif
}
