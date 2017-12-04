 //生产者

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //初始化互斥量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER; //初始化条件变量
static int avail = 0;

s = pthread_mutex_lock(&mtx); //锁定互斥量
if(s != 0)
	errExitEN(s, "pthread_mutex_lock");
avail++;

s = pthread_mutex_unlock(&mtx); //解锁互斥量
if(s!=0)
	errExitEN(s, "pthread_mutex_unlock");

s = pthread_cond_signal(&cond);  //发送条件变量信号
if(s!=0)
	errExitEN(s, "pthread_cond_signal");

//消费者
for (;;) {
	s = pthread_mutex_lock(&mtx);

	if(s!=0)
		errExitEN(s, "pthread_mutex_lock");

	while (avail == 0) {
		s = pthread_cond_wait(&cond, &mtx);
		if(s!=0)
			errExitEN(s, "pthread_cond_wait");
	}

	while (avail > 0) {
		avail--;
	}

	s = pthread_mutex_unlock(&mtx);
	if(s!=0)
		errExitEN(s, "pthread_mutex_unlock");
}