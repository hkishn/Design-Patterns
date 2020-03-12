/**
 * Include headers 
 */
#include<iostream>

/**
 * FlyBehavior is an interface that \
 * all flying classes implement. All \
 * new flying classess just need to \
 * implement the fly method.
 */
class FlyBehavior
//-------------------------------------------------------------------------------
{
	public:
		virtual void fly() = 0;
};
//-------------------------------------------------------------------------------

/**
 * Implementation of flying for all ducks that have wings 
 */
class FlyWithWings: public FlyBehavior
//-------------------------------------------------------------------------------
{
	public:
		void fly()
		{
			std::cout<<"\n Flying"<<std::endl;
		}
};
//-------------------------------------------------------------------------------

/**
 * Implementation of all ducks that can't fly
 */
class FlyNoWay: public FlyBehavior
//-------------------------------------------------------------------------------
{
	public:
		void fly()
		{
			std::cout<<"\n Do nothing. Can't fly"<<std::endl;
		}
};
//-------------------------------------------------------------------------------

/**
 * Implementation of all ducks that can fly with rocket power
 */
class FlyRocketPowered: public FlyBehavior
//-------------------------------------------------------------------------------
{
	public:
		void fly()
		{
			std::cout<<"\n I am flying with a rocket!"<<std::endl;
		}
};
//-------------------------------------------------------------------------------

/**
 * QuackBehavior is an interface that \
 * all quacking classes implement. All \
 * new quacking classess just need to \
 * implement the quack method.
 */
class QuackBehavior
//-------------------------------------------------------------------------------
{
	public:
		virtual void quack() = 0;
};
//-------------------------------------------------------------------------------

/**
 * Implementation of all ducks that quack
 */
class Quack: public QuackBehavior
//-------------------------------------------------------------------------------
{
	public:
		void quack()
		{
			std::cout<<"\n Quacking"<<std::endl;
		}
};
//-------------------------------------------------------------------------------

/**
 * Implementation of all ducks that squeak 
 */
class Squeak: public QuackBehavior
//-------------------------------------------------------------------------------
{
	public:
		void quack()
		{
			std::cout<<"\n Queak"<<std::endl;
		}
};
//-------------------------------------------------------------------------------

/**
 * Implementation of all ducks that make no sound at all
 */
class MuteQuack: public QuackBehavior
//-------------------------------------------------------------------------------
{
	public:
		void quack()
		{
			std::cout<<"\n Do nothing."<<std::endl;
		}
};
//-------------------------------------------------------------------------------


/**
 * Implementation of Duck
 */

class Duck
//-------------------------------------------------------------------------------
{
	public:
		QuackBehavior *quackBehavior; /*!< Each duck has a reference to somthing that implements the QuackBehavior interface */
		FlyBehavior *flyBehavior; /*!< Each duck has a reference to somthing that implements the FlyBehavior interface */

		void performQuack()
		{
			quackBehavior->quack(); /*< the Duck object delegates that behavior to the object referenced by quackBehavior */
		}

		void performFly()
		{
			flyBehavior->fly(); /*< the Duck object delegated the fly behavior */
		}
		
		virtual void display() = 0;
                
		/**
		 * Set the duck's behavior type through setters method on the duck subclass,
		 * rather than by instantiating it in the ducks's constructor
		 */
		void setFlyBehavior(FlyBehavior *fb)
		{	
			if ((nullptr != flyBehavior) && (nullptr != fb))
			{
				flyBehavior = fb;
			}
		}

		void setQuackBehavior(QuackBehavior *qb)
		{
			if ((nullptr != quackBehavior) && (nullptr !=qb))
			{
				quackBehavior = qb;
			}
		}

};
//-------------------------------------------------------------------------------

class MallardDuck: public Duck
//-------------------------------------------------------------------------------
{
	public:
		MallardDuck()
		{
			quackBehavior = new Quack(); /*!< A MallardDuck uses the Quack class to handle its quack, so when the performQuack is called 
						          the responsibility for the quack is delegated to the Quack object and we get a real quack */
			flyBehavior = new FlyWithWings(); /*!< Uses FlyWithWings as its FlyBehavior type */
		}

		void display()
		{
			std::cout<<"\n I am a real Mallard Duck"<<std::endl;
		}

		~MallardDuck() /*!< Delete/free the memory created on heap. This will not cause memory leak in the real application */
		{
			if (nullptr != quackBehavior)
			{
				delete [] quackBehavior;
				quackBehavior = nullptr;
			}
			if (nullptr != flyBehavior)
			{
				delete [] flyBehavior;
				flyBehavior = nullptr;
			}
		}

};
//-------------------------------------------------------------------------------

/**
 * class to simulate dynamic behavior of the TestDuck behavior
 */
class TestDuck: public Duck
//-------------------------------------------------------------------------------
{
	public:
		TestDuck()
		{
			quackBehavior = new Quack(); 
			flyBehavior = new FlyNoWay();
		}

		void display()
		{
			std::cout<<"\n I am a test duck. Play with me"<<std::endl;
		}

		~TestDuck()
		{
			if (nullptr != quackBehavior)
			{
				delete [] quackBehavior;
				quackBehavior = nullptr;
			}
			if (nullptr != flyBehavior)
			{
				delete [] flyBehavior;
				flyBehavior = nullptr;
			}
		}

};
//-------------------------------------------------------------------------------

/**
 * Simulation code 
 */

int main()
{
	Duck *mallard = new MallardDuck();
	mallard->display();
	mallard->performQuack(); /*!< This calls the MallardDuck'inherited performQuack() method , which then delegates to object's QuackBehavior */
	mallard->performFly();  /*!< This does the same thing with MallardDuck's inherited performFly() method */
	delete mallard;
	/**
	 * output:
	 * I am a real Mallard Duck
	 * 
	 * Quacking
	 *
	 * Flying
	 */
        /**
	 * Setting behavior dynamically
	 */

	Duck* testduck = new TestDuck();
	testduck->display();
	testduck->performFly();
	FlyRocketPowered* rocketfly = new FlyRocketPowered();
	testduck->setFlyBehavior(rocketfly); /*!< This invokes the test duck inherited behavior setter method. This makes the test duck fly */
	testduck->performFly();
	delete testduck;
	/**
	 * output:
	 *
	 *  I am a test duck. Play with me
	 *  
	 *  Do nothing. Can't fly
	 *
	 *  I am flying with a rocket!
	 */


	return 0;
}
