#ifndef UNTITLED_SINGELTON_H
#define UNTITLED_SINGELTON_H

template <typename C>
class Singleton
{
public:
   template < class E > static C* instance (E val){
      if (!_instance)
         _instance = new C (val);
      return _instance;
   }

   static C* instance (){
      if (!_instance)
         _instance = new C ();
      return _instance;
   }
   static void destroyInstance(){
     if (_instance)
        delete(_instance);
      _instance = 0;
   }
   virtual ~Singleton (){
      _instance = 0;
   }

private:
   static C* _instance;
protected:
   Singleton () { }
};

template <typename C> C* Singleton <C>::_instance = 0;

#endif
