package ru.rustore.unitysdk.review;

public interface ReviewResponseListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess();
}