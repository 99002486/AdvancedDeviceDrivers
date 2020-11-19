#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

static void simple_work_handler(struct work_struct *w);

//struct work_struct simple_work;
//struct delayed_work simple_delayed_work;

static DECLARE_WORK(simple_work, simple_work_handler);
//static DECLARE_DELAYED_WORK(simple_delayed_work, simple_work_handler);

static unsigned long onesec;

static void simple_work_handler(struct work_struct *w)
{
  pr_info("simple work %u jiffies\n", (unsigned)onesec);
}


static int __init wqsimple_init(void)
{
  onesec = msecs_to_jiffies(1000);
  pr_info("wqsample loaded %u jiffies\n", (unsigned)onesec);

  //INIT_WORK(&simple_work, simple_work_handler, onesec);
  //INIT_DELAYED_WORK(&simple_delayed_work, simple_work_handler, onesec);

  schedule_work(simple_work); 
  //schedule_delayed_work(&simple_delayed_work,onesec);
  return 0;
}

static void __exit wqsimple_exit(void)
{
  //flush_scheduled_work
  //cancel_delayed_work
  pr_info("wqsimple exit\n");
}

module_init(wqsimple_init);
module_exit(wqsimple_exit);

MODULE_DESCRIPTION("Work Queue Example");
MODULE_LICENSE("GPL");
