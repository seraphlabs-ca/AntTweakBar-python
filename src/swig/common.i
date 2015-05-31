/* A common file to be included in all interface files */
%feature("autodoc", "3");
%include "exception.i"

// setup exceptions handler
%exception {
	try{
		$action
		}
	catch (const std::string& err_msg) {
		SWIG_exception(SWIG_RuntimeError, err_msg.c_str());
		return NULL;
   }
	catch (const char*& err_msg) {
		SWIG_exception(SWIG_RuntimeError, err_msg);
		return NULL;
   }
	catch (...) {
		SWIG_exception(SWIG_RuntimeError, "Unknown error");
		return NULL;
	}
}
