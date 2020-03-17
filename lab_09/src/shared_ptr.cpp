#include "shared_ptr.hpp"
#include "matrix.hpp"
#include <algorithm>


shared_ptr::Storage::Storage(Matrix* mtx) :
		data_(mtx), ref_count_(1) {}

shared_ptr::Storage::~Storage() {
	delete data_;
}

void shared_ptr::Storage::incr() {
	ref_count_++;
}

void shared_ptr::Storage::decr() {
	ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
	return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
	return data_;
}


shared_ptr::shared_ptr(Matrix* obj) {
	create_storage(this, obj);
}

shared_ptr::~shared_ptr() {
	decr_and_check(this);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
	storage_ = other.storage_;
	if (storage_ != nullptr) {
		storage_->incr();
	}
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	std::swap(storage_, other.storage_);
	return *this;
}

void shared_ptr::decr_and_check(shared_ptr* cur_ptr) {
	if (cur_ptr->storage_ != nullptr) {
		cur_ptr->storage_->decr();
		if (cur_ptr->storage_->getCounter() == 0) {
			delete cur_ptr->storage_;
			cur_ptr->storage_ = nullptr;
		}
	}
}

void shared_ptr::create_storage(shared_ptr* cur_ptr, Matrix* obj) {
	if (obj == nullptr) {
		cur_ptr->storage_ = nullptr;
	} else {
		cur_ptr->storage_ = new Storage(obj);
	}
}

Matrix* shared_ptr::ptr() const {
	if (storage_ == nullptr) {
		return nullptr;
	} else {
		return storage_->getObject();
	}
}

bool shared_ptr::isNull() const {
	return storage_ == nullptr;
}

void shared_ptr::reset(Matrix* obj) {
	decr_and_check(this);
	create_storage(this, obj);
}

Matrix* shared_ptr::operator->() const {
	return ptr();
}

Matrix& shared_ptr::operator*() const {
	return *ptr();
}