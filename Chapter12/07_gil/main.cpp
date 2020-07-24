#include <png.h>

// MinGW workarounds for https://svn.boost.org/trac10/ticket/3908 :
#ifndef png_infopp_NULL
#   define png_infopp_NULL NULL
#endif
#ifndef int_p_NULL
#   define int_p_NULL NULL
#endif

#include <boost/version.hpp>
#if (BOOST_VERSION < 106800)
#   include <boost/gil/gil_all.hpp>
#   include <boost/gil/extension/io/png_dynamic_io.hpp>
#else
#   include <boost/gil.hpp>
#   include <boost/gil/extension/io/png/old.hpp>
#endif
#include <boost/mpl/vector.hpp>

#include <string>

#include <cassert>

struct negate {
    typedef void result_type; // required

    template <class View>
    void operator()(const View& source) const {

// Code formatting is shifted left to fit page width
boost::gil::gil_function_requires<
    boost::gil::ImageViewConcept<View>
>();

typedef typename View::value_type value_type;
typedef typename boost::gil::channel_type<value_type>::type channel_t;

const std::size_t channels = boost::gil::num_channels<View>::value;
const channel_t max_val = (std::numeric_limits<channel_t>::max)();

for (unsigned int y = 0; y < source.height(); ++y) {
    for (unsigned int x = 0; x < source.width(); ++x) {
        for (unsigned int c = 0; c < channels; ++c) {
            source(x, y)[c] = max_val - source(x, y)[c];
        }
    }
}


    }
}; // negate

int main(int argc, char *argv[]) {
    assert(argc == 2);

#if (BOOST_VERSION < 107400)
    typedef boost::mpl::vector3<
            boost::gil::gray8_image_t,
            boost::gil::gray16_image_t,
            boost::gil::rgb8_image_t
    > img_types;
    boost::gil::any_image<img_types> source;
#else
    // Boost.GIL now uses variadic templates
    boost::gil::any_image<
            boost::gil::gray8_image_t,
            boost::gil::gray16_image_t,
            boost::gil::rgb8_image_t
    > source;
#endif

    std::string file_name(argv[1]);
    boost::gil::png_read_image(file_name, source);

    boost::gil::apply_operation(
        view(source),
        negate()
    );

    boost::gil::png_write_view("negate_" + file_name, const_view(source));
}
