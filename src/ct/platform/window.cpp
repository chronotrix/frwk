

#include <ct/core/config/os_detection.hpp>
#include <ct/core/assert/assert.hpp>
#include <ct/core/utils/type_traits.hpp>
#include <ct/platform/window.hpp>

#if defined(CT_OS_WIN32)

	#include <ct/platform/win32/win32_window.hpp>
typedef ct::internal::Win32Window WindowImplType;

#elif defined(CT_OS_MACOS)

	#include <ct/platform/osx/cocoa_window.hpp>
typedef ct::internal::CocoaWindow WindowImplType;

#else

	#error "Platform not supported"

#endif

namespace ct {

	WindowPtr create_window(uint32 width, uint32 height, cstr title, uint32 style) {

		WindowProperties props(
			width,
			height,
			title,
			style
		);

		return create_window(props);

	}

	WindowPtr create_window(const WindowProperties & props) {
		auto impl = WindowImplType::create(props);
		return std::make_unique<enable_make<Window>>(impl);
	}



	Window::Window(WindowImpl * _impl) {
		CT_ASSERT(_impl != NULLPTR, "ct::Window: impl is nullptr.");
		this->impl = WindowImplPtr(_impl);
	}

	Window::~Window() {
		close();
	}

	bool Window::is_visible() const {
		return impl && impl->is_visible();
	}

	WindowHandle Window::get_handle() const {
		return impl ? impl->get_handle() : NULLPTR;
	}

	void Window::set_visible(bool visible) {
		if (impl) {
			impl->set_visible(visible);
		}
	}

	void Window::close() {
		impl.reset(NULLPTR);
	}
} // namespace ct