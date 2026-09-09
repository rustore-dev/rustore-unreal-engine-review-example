package ru.rustore.unrealsdk.review;

public interface ReviewResponseListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess();
}
